const INSERTION_COST = 1;
const DELETE_COST = 1;
const REPLACE_COST = 1;

function levensteinDistance(wordA, wordB)
{
    // D[i][j] = D[i + j*x]
    // x = ordA.length; y = wordB.length
    // wordA = horizontal, wordB = vertical
    // | | |w|o|r|d|A|
    // ---------------
    // | | | | | | | |
    // ---------------
    // |w| | | | | | |
    // ---------------
    // |o| | | | | | |
    // ---------------
    // |r| | | | | | |
    // ---------------
    // |d| | | | | | |
    // ---------------
    // |B| | | | | | |
    // ---------------
    var D = [];

    let x = wordA.length + 1;
    let y = wordB.length;

    for(let i = 0; i < x; i++)
        D[i] = i;
    for(let j = 0; j <= y; j++)
        D[j*x] = j;
    for(let i = 1; i < x; i++)
        for(let j = 1; j <= y; j++)
        {
            let cost = wordA[i-1] == wordB[j-1] ? 0 : REPLACE_COST;
            D[i + j*x] = Math.min
            (
                D[i + (j-1)*x] + INSERTION_COST,
                D[i-1 + j*x] + DELETE_COST,
                D[i-1 + (j-1)*x] + cost
            );
        }

    return D;
}

module.exports.levensteinDistance = levensteinDistance;