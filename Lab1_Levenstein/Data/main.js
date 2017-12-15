const Http = fetches();

const table = createTable(0);
const dtable = createTable(1);
let recursiveStart = 0;

const actionButton = document.getElementById("button");
actionButton.addEventListener("click", function()
{
    let textA = document.getElementById("wordA").value;
    let textB = document.getElementById("wordB").value;
    let arg = {wordA: textA, wordB: textB};
    Http.FetchPost("/levenstein", arg)
        .then((response) =>
    {
        drawResult(response, table, resultField, conversionRule, ruleNode);
    });
    recursiveStart = performance.now();
    Http.FetchPost("/levensteinRecursive", arg)
        .then((response) =>
    {
        alert("Execution time: " + (performance.now() - recursiveStart));
        recursiveResultField.innerHTML = response.value;
    });
    Http.FetchPost("/damerauLevenstein", arg)
        .then((response) =>
    {
        drawResult(response, dtable, damerauResultField, damerauConversionRule, damerauRuleNode);
    });
    Http.FetchPost("/damerauLevensteinRecursive", arg)
        .then((response) =>
    {
        damerauRecursiveResultField.innerHTML = response.value;
    })
});

const resultField = document.getElementById("levensteinResult");
const recursiveResultField = document.getElementById("levensteinRecursiveResult");
const ruleNode = document.getElementById("rule");
const HEADER_COLOR = "#3b1513";
const damerauResultField = document.getElementById("damerauLevensteinResult");
const damerauRecursiveResultField = document.getElementById("damerauLevensteinRecursiveResult");
const damerauRuleNode = document.getElementById("dlRule");

function createTable(id)
{
    let table = document.createElement("table");
    table.className = "table";
    let holder = document.getElementsByClassName("matrixHolder")[id];
    holder.appendChild(table);

    return table;
}

function drawResult(data, table, resultField, conversionRule, ruleNode)
{
    let textA = document.getElementById("wordA").value;
    let textB = document.getElementById("wordB").value;
    const x = textA.length + 1;
    const y = textB.length + 1;

    clearNode(table);
    {
        let hRow = document.createElement("tr");
        for (let i = 0; i < 2; i++)
        {
            let td = document.createElement("td");
            td.innerHTML = " ";
            td.style.borderColor = HEADER_COLOR;
            hRow.appendChild(td);
        }

        let _x = x-1;
        for (let i = 0; i < _x; i++)
        {
            let td = document.createElement("td");
            td.innerHTML = textA[i];
            td.style.borderColor = HEADER_COLOR;
            hRow.appendChild(td);
        }
        table.appendChild(hRow);
    }


    for(let j = 0; j < y; j++)
    {
        let row = document.createElement("tr");
        {
            let td = document.createElement("td");
            td.style.borderColor = HEADER_COLOR;
            row.appendChild(td);

            if(j == 0)
                td.innerHTML = " ";
            else
                td.innerHTML = textB[j-1];
        }
        for(let i = 0; i < x; i++)
        {
            let td = document.createElement("td");
            td.innerHTML = data[i + j*x];
            row.appendChild(td);
        }
        table.appendChild(row);
    }

    resultField.innerHTML = data[x*y - 1];
    conversionRule(textA, textB, data, ruleNode);
}

function conversionRule(textA, textB, data, ruleNode)
{
    let x = textA.length + 1;
    let y = textB.length + 1;
    let i = x - 1;
    let j = y - 1;

    let ruleString = "";

    while(i > 0 || j > 0)
    {
        let diag = Infinity;
        let left = Infinity;
        let upper = Infinity;

        if(i > 0 && j > 0)
            diag = data[(i-1) + (j-1)*x];
        if(i > 0)
            left = data[i-1 + j*x];
        if(j > 0)
            upper = data[i + (j-1)*x];

        if(diag <= left && diag <= upper)
        {
            if(diag < data[i + j*x])
                ruleString = 'R' + ruleString;
            else
                ruleString = 'M' + ruleString;
            i--;j--;
        }
        else if(left <= diag && left <= upper)
        {
            ruleString = 'D' + ruleString;
            i--;
        }
        else
        {
            ruleString = 'I' + ruleString;
            j--;
        }
    }

    drawConversionRule(ruleString, ruleNode)
}

function damerauConversionRule(textA, textB, data, ruleNode)
{
    let x = textA.length + 1;
    let y = textB.length + 1;
    let i = x - 1;
    let j = y - 1;

    let ruleString = "";
    let transpose = false;

    while(i > 0 || j > 0)
    {
        let diag = Infinity;
        let left = Infinity;
        let upper = Infinity;

        if(i > 0 && j > 0)
            diag = data[(i-1) + (j-1)*x];
        if(i > 0)
            left = data[i-1 + j*x];
        if(j > 0)
            upper = data[i + (j-1)*x];

        if(diag <= left && diag <= upper)
        {
            if(diag < data[i + j*x])
            {
                if(transpose)
                {
                    ruleString = 'T' + ruleString;
                    transpose = false;
                }
                else
                    ruleString = 'R' + ruleString;
            }
            else if(textA[i-1] == textB[j-2] && textA[i-2] == textB[j-1])
            {
                ruleString = 'T' + ruleString;
                transpose = true;
            }
            else
                ruleString = 'M' + ruleString;
            i--;j--;
        }
        else if(left <= diag && left <= upper)
        {
            ruleString = 'D' + ruleString;
            i--;
        }
        else
        {
            ruleString = 'I' + ruleString;
            j--;
        }
    }

    drawConversionRule(ruleString, ruleNode)
}

function drawConversionRule(rule, ruleNode)
{
    clearNode(ruleNode);

    for(let i = 0; i < rule.length; i++)
    {
        let elem = document.createElement("span");
        elem.textContent = rule[i];
        switch(rule[i])
        {
            case 'M': elem.className = "match"; break;
            case 'R': elem.className = "replace"; break;
            case 'I': elem.className = "insert"; break;
            case 'D': elem.className = "delete"; break;
            case 'T': elem.className = "transpose"; break;
        }
        ruleNode.appendChild(elem);
    }
}

function clearNode(node)
{
    while(node.hasChildNodes())
        node.removeChild(node.firstChild);
}