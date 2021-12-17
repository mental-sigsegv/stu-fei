ret1='vecera'
ret2=''
for i in range(len(ret1)):
   if ret1[i] not in ret1[i+1:]:
      ret2=ret2+ret1[i]
print(ret2)
