# hitokoto

在终端中获取[一言](https://hitokoto.cn)，使用libcurl和json-c

## 安装

### Homebrew

```zsh
brew tap moesnow/tools
brew install hitokoto
```

## 依赖

### Debian/Ubuntu

```bash
sudo apt install libcurl4-openssl-dev libjson-c-dev
```

### macOS

```bash
brew install json-c
```

## 编译

```bash
git clone https://github.com/moesnow/hitokoto.git
cd hitokoto
make
# optional
sudo make install
```

## 用法

```bash
./hitokoto
```

