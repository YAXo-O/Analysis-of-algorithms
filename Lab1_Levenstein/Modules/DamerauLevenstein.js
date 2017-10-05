const INSERTION_COST = 1;
const DELETE_COST = 1;
const REPLACE_COST = 1;
const TRANSPOSITION_COST = 1;

function damerauLevenstein(wordA, wordB)
{
    let D = [];
    let x = wordA.length + 1;
    let y = wordB.length + 1;

    for(let i = 0; i < x; i++)
        D[i] = i;
    for(let j = 0; j < y; j++)
        D[j*x] = j;
    for(let j = 1; j < y; j++)
    {
        for(let i = 1; i < x; i++)
        {
            let cost = wordA[i-1] == wordB[j-1] ? 0 : REPLACE_COST;
            D[i + j * x] = Math.min
            (
                D[i-1 + j*x] + DELETE_COST,
                D[i+(j-1)*x] + INSERTION_COST,
                D[i-1 + (j-1)*x] + cost
            );

            if (i > 0 && j > 1 && wordA[i-1] == wordB[i-2] && wordA[i-2] == wordB[i-1])
            {
                D[i + j*x] = Math.min
                (
                    D[i + j*x],
                    D[i-2 + (j-2)*x] + TRANSPOSITION_COST
                );
            }

        }
    }

    return D;
}

module.exports.damerauLevenstein = damerauLevenstein;