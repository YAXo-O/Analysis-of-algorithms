const INSERTION_COST = 1;
const DELETE_COST = 1;
const REPLACE_COST = 1;
const TRANSPOSITION_COST = 1;

function damerauLevenstein(wordA, wordB)
{
    function D(i, j)
    {
        if (i == j && j == 0)
            return 0;
        if (i == 0 && j > 0)
            return j;
        if (j == 0 && i > 0)
            return i;

        if (i > 0 && j > 0)
        {
            let cost = wordA[i-1] == wordB[j-1] ? 0 : REPLACE_COST;
            let levensteinValue = Math.min
            (
                D(i-1, j) + DELETE_COST,
                D(i, j-1) + INSERTION_COST,
                D(i-1, j-1) + cost
            );
            if (i > 0 && j > 1 && wordA[i-1] == wordB[i-2] && wordA[i-2] == wordB[i-1])
                levensteinValue = Math.min
                (
                    levensteinValue,
                    D(i-2, j-2) + TRANSPOSITION_COST
                );

            return levensteinValue;
        }

    }

    return {value: D(wordA.length + 1, wordB.length + 1)};
}

module.exports.damerauLevenstein = damerauLevenstein;