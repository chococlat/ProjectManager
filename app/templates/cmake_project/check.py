with open("_config.dc","r") as c:
    s = c.read();

for c in s:
    if c=='\n':
        print('\\n',end='')
    elif c=='\t':
        print('\\t',end='')
    elif c=='\r':
        print('\\r',end='')
    elif c=='\s':
        print('\\s',end='')
    elif c=='\b':
        print('\\b',end='')
    elif c==' ':
        print('\s',end='')
    else:
        print(c,end='')