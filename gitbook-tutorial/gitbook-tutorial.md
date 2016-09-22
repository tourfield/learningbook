1. 安装npm
```
sudo apt-get install npm
```
2. 安装gitbook
```
sudo npm install -g gitbook-cli
```
3. 安装pdf生成工具
```
sudo -v && wget -nv -O- https://raw.githubusercontent.com/kovidgoyal/calibre/master/setup/linux-installer.py | sudo python -c "import sys; main=lambda:sys.stderr.write('Download failed\n'); exec(sys.stdin.read()); main()"
```
使用实例：

1. 创建README.md、SUMMARY.md
```
touch README.md SUMMARY.md
```
2. 编辑SUMMARY.md，内容如下：
```
* [简介](README.md)
* [第一章](chapter1/README.md)
 - [第一节](chapter1/section1.md)
 - [第二节](chapter1/section2.md)
* [第二章](chapter2/README.md)
 - [第一节](chapter2/section1.md)
 - [第二节](chapter2/section2.md)
* [结束](end/README.md)
```
3. 生成简书目录
```
gitbook init .
```
4. 本地预览执行下面命令，在浏览器中输入然后浏览器中输入 http://localhost:4000 就可以预览网页
```
gitbook serve .
```
5. 生成静态网页，执行下面命令
```
gitbook build --output=/tmp/gitbook
```
6. 生成PDF文件，执行下面命令
```
gitbook pdf .
```
7. 生成电子书
```
gitbook epub .
```

8. 将以上步骤写入makefile中，执行make便可以生成所有的文件；makefile中内容如下：
``` makefile
# ==============================================================================
# make all/pdf/epub/mobi/clean
# ==============================================================================
GITBOOK = gitbook
RM = rm

TARGET = SELinux说明
FORMATS = pdf epub mobi

.PHONY: all clean html $(FORMATS)

all: html $(FORMATS)

html:
	$(GITBOOK) build . $(TARGET)_html

$(FORMATS):
	$(GITBOOK) $@ . $(TARGET).$@
init:
  $(GITBOOK) init

preview:
  $(GITBOOK) serve

clean:
	-$(RM) -f $(addprefix $(TARGET)., $(FORMATS))
	-$(RM) -rf $(TARGET)_html
```
