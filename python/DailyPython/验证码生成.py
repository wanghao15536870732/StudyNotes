# 做为 Apple Store App 独立开发者，你要搞限时促销，为你的应用生成激活码（或者优惠券）
# 如何使用 Python 如何生成 200 个激活码（或者优惠券）？
from random import randint

# length 每个激活码的长度
# number 所有激活码的总长度
def makecode(length,number):
    code = [] # 新建空的ser
    code_set = set(code) # code的集合
    code_map = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"  # 导入各种字母
    limit = len(code_map) #计算长度
    while(len(code_set) < number): # 计算长度小于总产度
        this_code = "" # 创建一个新的列表
        for i in range(length):
            this_code += code_map[randint(0,limit -1)]  # 随机添加
        code.append(this_code) #添加到code的后面
        code_set = set(code)
    return code_set # 返回集合
if __name__ == '__main__':
    for i in makecode(4,200): # 遍历刚刚返回的集合，填入长度以及
        print(i)