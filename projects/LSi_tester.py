from itertools import product
from pprint import pprint


def y(i):
    a, b = i

    return a&(not(a&(not b)))&(not (a&b))

def z(i):
    a, b= i
    return 0
    return int( (not a)|((not b)&(not c)) )


# pprint([bin_combination for bin_combination in product([0,1], repeat=3)])

import pandas as pd
import numpy as np

import pandas as pd
import numpy as np


combinations = ['A   B   C']+[bin_combination for bin_combination in product([0,1], repeat=2)]
result = [['-', '-']]+[[y(comb), z(comb)] for comb in combinations[1:]]
df = pd.DataFrame(result,
                  index=pd.Index(combinations),
                  columns=pd.MultiIndex.from_product([['Result', 'Mine']]))
print(df)