# 将你的 QQ 头像（或者微博头像）右上角加上红色的数字，
# 类似于微信未读信息数量那种提示效果。 

from PIL import Image,ImageDraw,ImageFont

def add_num(img):
    draw = ImageDraw.Draw(img) # 打开图像进行画图
    myfont = ImageFont.truetype('C:/windows/fonts/Arial.ttf',size=40) #设置字体跟大小
    fillcolor = '#ff0000' # 设置字体跟颜色
    width,height = img.size  # 保存照片的长度宽度
    draw.text((width-160,0),'lena',font=myfont,fill=fillcolor) # 在图像上进行draw
    img.save('result.jpg','jpeg') # 保存一下图片
    return 0

if __name__ == '__main__':
    image = Image.open('D:\\Desktop\\picture\\lena.jpg') # 打开图像
    add_num(image) # 调用函数