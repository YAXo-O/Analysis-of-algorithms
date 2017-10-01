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
    clearNode(ruleNode);

    let i = textA.length + 1;
    let j = textB.length + 1;

}


function clearNode(node)
{
    while(node.hasChildNodes())
        node.removeChild(node.firstChild);
}