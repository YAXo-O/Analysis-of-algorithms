const Http = fetches();

const table = document.createElement("table");
const matrixHolder = document.getElementsByClassName("matrixHolder")[0];
matrixHolder.appendChild(table);
table.className = "table"

const actionButton = document.getElementById("button");
actionButton.addEventListener("click", function()
{
    var textA = document.getElementById("wordA").value;
    var textB = document.getElementById("wordB").value;
    Http.FetchPost("/levenstein", {wordA: textA, wordB: textB})
        .then((response) =>
    {
        drawResult(response);
    });
});


function drawResult(result)
{
    debugger;
    const data = result.result;
    const x = result.x;
    const y = result.y;

    for(let j = 0; j < y; j++)
    {
        var row = document.createElement("tr");
        for(let i = 0; i < x; i++)
        {
            var td = document.createElement("td");
            td.innerHTML = data[i + j*x];
            row.appendChild(td);
        }
        table.appendChild(row);
    }
}