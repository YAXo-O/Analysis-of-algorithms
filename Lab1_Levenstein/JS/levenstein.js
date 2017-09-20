var D = [];
var wordA;
var wordB;
const INSERTION_COST = 1;
const REMOVAL_COST = 1;
const REPLACEMENT_COST = 1;

function count()
{
    // Preparing initial matrix for comparison
    let alen = wordA.value.length;
    let blen = wordB.value.length;
    D = new Array(alen);
    for(let i = 0; i <= alen; i++)
    {
        D[i] = new Array(blen);
        for(let j = 0; j <= blen; j++)
            D[i][j] = 0;
    }

    // Calculating distance
    levenstein();
    levensteinRec();
    levensteinSwap();

    let fc = table.firstChild;
    while(fc)
    {
        table.removeChild(fc);
        fc = table.firstChild;
    }
    drawMatrix();
}

// Code to be run
var submit = (document.getElementsByName("Count"))[0];
submit.addEventListener("click", count);
wordA = (document.getElementsByName("WordA"))[0];
wordB = (document.getElementsByName("WordB"))[0];
var outLev = document.getElementById("ld");
var outLevRec = document.getElementById("ld_rec");
var outLevSwap = document.getElementById("ld_swap");
var table = document.createElement("table");
table.className = "matrix-table";
var tableDiv = (document.getElementsByClassName("matrix-output"))[0];
tableDiv.appendChild(table);

function levenstein()
{
    let alen = wordA.value.length;
    let blen = wordB.value.length;

    for(let j = 0; j < blen; j++)
        D[0][j+1] = D[0][j] + INSERTION_COST;
    for(let i = 0; i < alen; i++)
    {
        D[i+1][0] = D[i][0] + REMOVAL_COST;
        for(let j = 0; j < blen; j++)
            D[i+1][j+1] = Math.min(
                D[i][j+1] + REMOVAL_COST,
                D[i+1][j] + INSERTION_COST,
                D[i][j] + REPLACEMENT_COST);

    }

    outLev.innerHTML = D[alen][blen];
}

function levensteinRec()
{
    outLevRec.innerHTML = 0;
}

function levensteinSwap()
{
    outLevSwap.innerHTML = 0;
}

function drawMatrix()
{
    let alen = wordA.value.length;
    let blen = wordB.value.length;

    // Making header
    var title = document.createElement("tr");
    table.appendChild(title);
    var eCell = document.createElement("td");
    eCell.className = "matrix-header";
    title.appendChild(eCell);

    for(let i = 0; i < blen; i++)
    {
        var tCell = document.createElement("td");
        tCell.innerHTML = wordB.value[i];
        tCell.className = "matrix-header";
        title.appendChild(tCell);
    }

    // Rest of the matrix
    for(let i = 0; i < alen; i++)
    {
        var row = document.createElement("tr");
        var wordCell = document.createElement("td");
        wordCell.innerHTML = wordA.value[i];
        wordCell.className = "matrix-header";
        row.appendChild(wordCell);

        for(let j = 0; j < blen; j++)
        {
            var cell = document.createElement("td");
            cell.innerHTML = D[i+1][j+1];
            cell.className = "matrix-table-cell";
            row.appendChild(cell);
        }
        table.appendChild(row);
    }
}
