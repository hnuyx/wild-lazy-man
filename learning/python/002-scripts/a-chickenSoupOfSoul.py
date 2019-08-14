#!/usr/bin/python
# -*- coding: UTF-8 -*-

import random
import jieba

#file_name = "./2-dataset.txt"
#file_name = "./4-xljt.txt"
file_name = "./5-xljt.txt"
fo = open(file_name, "r", encoding='UTF-8')

model = {}
res = [list(jieba.cut(line)) for line in fo]
#res = ["".join(i) for i in res]
#print res
for index in range(len(res)):
    line = res[index]
    for i, word in enumerate(line):
        if i == len(line)-1:
            model['END'] = model.get('END', []) + [word]
        else:
            if i == 0:
                model['START'] = model.get('START', []) + [word]
            model[word] = model.get(word, []) + [line[i+1]]

i = 1
for i in range(1,10):
    generated = []
    while True:
        if not generated:
            words = model['START']
        elif generated[-1] in model['END']:
            break
        else:
            words = model[generated[-1]]
        generated.append(random.choice(words))
    print("".join(generated))

