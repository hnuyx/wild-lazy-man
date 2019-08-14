
import jieba
import pandas as pd

pd.set_option('max_colwidth', 200)
#pd.set_option('display.max_rows', None)

file_name = "./2-dataset.txt"
fo = open(file_name, "r", encoding='UTF-8')

res = [list(jieba.cut(line)) for line in fo]
ret = [" ".join(i) for i in res]
print(pd.DataFrame(ret))
