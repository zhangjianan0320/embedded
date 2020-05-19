#########################################################################
# File Name: build.sh
# Author: zjn
# mail: zjn
# Created Time: 2020年05月18日 星期一 15时33分02秒
#########################################################################
#!/bin/bash
convert temp.jpg -font NotoSansHans-Regular.otf -fill "rgb(255,0,0)" -posterize 500 -annotate 0x0+200+200 "大家好" new.jpg
