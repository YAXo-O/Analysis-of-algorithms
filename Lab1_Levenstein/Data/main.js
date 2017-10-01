const Http = fetches();

const table = document.createElement("table");
const matrixHolder = document.getElementsByClassName("matrixHolder")[0];
matrixHolder.appendChild(table);
table.className = "table"

const actionButton = document.getElementById("button");
actionButton.addEventListener("click", function()
{
    let textA = document.getElementById("wordA").value;
    let textB = document.getElementById("wordB").value;
    let arg = {wordA: textA, wordB: textB};
    Http.FetchPost("/levenstein", arg)
        .then((response) =>
    {
        drawResult(response);
    });
    Http.FetchPost("/levensteinRecursive", arg)
        .then((response) =>
    {
        recursiveResultField.innerHTML = response.value;
    });
});

const resultField = document.getElementById("levensteinResult");
const recursiveResultField = document.getElementById("levensteinRecursiveResult");
const ruleNode = document.getElementById("rule");
const HEADER_COLOR = "#3b1513";

function drawResult(data)
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
    conversionRule(textA, textB, data);
}

function conversionRule(textA, textB, data)
{
    let x = textA.length + 1;
    let y = textB.length + 1;
    let i = x - 1;
    let j = y - 1;

    let ruleString = "";

    while(i > 0 || j > 0)
    {
        console.log(i + ";" + j);
        let diag = Infinity;
        let left = Infinity;
        let upper = Infinity;

        debugger;
        if(i > 0 && j > 0)
            diag = data[(i-1) + (j-1)*x];
        if(i > 0)
            left = data[i-1 + j*x];
        if(j > 0)
            upper = data[i + (j-1)*x];

        console.log(left + "; " + diag+ "; " + upper);

        if(diag <= left && diag <= upper)
        {
            if(diag < data[i + j*x])
                ruleString = 'I' + ruleString;
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
            ruleString = 'R' + ruleString;
            j--;
        }
    }

    drawConversionRule(ruleString)
}

function drawConversionRule(rule)
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
        }
        ruleNode.appendChild(elem);
    }
}

function clearNode(node)
{
    while(node.hasChildNodes())
        node.removeChild(node.firstChild);
}