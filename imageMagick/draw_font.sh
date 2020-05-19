#########################################################################
# File Name: draw_font.sh
# Author: zjn
# mail: zjn
# Created Time: 2020年05月18日 星期一 15时47分10秒
#########################################################################
#!/bin/bash
convert -size $1x$2 xc:"rgb(255,0,0)" label1.jpg
convert label.jpg -font NotoSansHans-Regular.otf -fill "rgb(0,255,0)" -pointsize 60 -annotate 0x0+0+60 "大家好:"  label.jpg
rm label1.jpg
#convert label.jpg -font NotoSansHans-Regular.otf -fill "rgb(0,255,0)" -pointsize 36 label:"hello" -annotate 0x0+0+0 "hello" label_temp.jpg
