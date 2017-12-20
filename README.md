# 개요
SIPSkia(Simple Image Processing by Skia) 는 [Skia](https://skia.org/)
기반의 간단한 이미지 resize, crop 을 수행하는 파이썬 라이브러리입니다.
각종 이미지 변환에 사용되고 있습니다.

# 목적
Skia 는 다른 이미지 처리 라이브러리와 비교하여 굉장히 빠른 성능과 낮은
CPU 사용률을 보입니다. 본 개발 작업을 진행하며 느낀 Skia 의 성능과
작은 노하우를 다른 분들과 공유하기 위한 목적으로 코드를 공개 하였습니다.

# 얼마나 빠른가?
Skia chrome/m52 브랜치와 [ImageMagick](https://www.imagemagick.org/) +
[Wand](http://docs.wand-py.org/en/0.4.4/) 3.x 때에는 5 ~ 6 배 이상의
성능 차이가 있었습니다만, chrome/m58 과 ImageMagick + Wand 4.x 기준으로
약 1.8 ~ 2배 정도의 성능 차이를 보입니다.

Skia 의 성능은 기존과 큰 차이가 없습니다만 ImageMagick, Wand 의 성능이
매우 좋아진 것으로 보입니다.

# 테스트 환경
sipskia 는 목적 상 매우 제한된 환경에서만 테스트 되었습니다.
즉 다음 환경이 아닌 곳에서의 정상 동작을 보장하지 않습니다.

## 공통
* Skia chrome/m64 브랜치
* python 3.6

## macOS
* macOS Sierra 이상
* boost-python 1.64.0

## ubuntu
* ubuntu 16.04
* boost-python 1.66.0

# 빌드 하기
## 의존성
sipskia 는 다음 버전에서 테스트 되었습니다. 아래 설치 방법이나 테스트 방법 모두
해당 버전을 기준으로 설명합니다.

* Python 3.6+
* [boost](http://www.boost.org/) 1.63.0 이상
* skia chrome/m64

### Python2 미지원
Python2 는 더 이상 지원하지 않습니다. python2 branch 에서 마지막 작업 현황을
확인 가능합니다.

# 준비
## macOS
### 1. boost-python 설치
brew 를 이용하면 깔끔하게 설치할 수 있습니다.
만일 기존 boost-python 이 python3 를 지원하지 않게 설치되어 있다면 제거한 후
새로 설치해야 합니다.

```bash
$ brew install boost-python --with-python3 --without-python
```

### 2. Skia 빌드
현재 Skia 는 chrome/m58 버전을 기준으로 빌드합니다. 그 뒤의 버전은 Skia 자체가
macOS 에서 빌드되지 않는 문제가 있는 것 같습니다.

```bash
$ git clone 'https://chromium.googlesource.com/chromium/tools/depot_tools.git'
$ export PATH="${PWD}/depot_tools:${PATH}"
$ git clone https://skia.googlesource.com/skia.git
$ cd skia
$ python tools/git-sync-deps
```

위와 같이 사전 준비를 진행한 후 [ninja](https://ninja-build.org/) 를 통해 Skia 를 Static Library
로 빌드합니다.
```bash
$ bin/gn gen out/Static --args='is_official_build=true skia_enable_gpu=true skia_use_fontconfig=false skia_use_system_expat=false skia_use_system_icu=false skia_use_system_libjpeg_turbo=false skia_use_system_libpng=false skia_use_system_libwebp=false skia_use_system_zlib=false cc="clang" cxx="clang++"'
$ ninja -C out/Static
```

정상적으로 빌드가 완료되면 out/Static 디렉토리에 libskia.a 파일이 생성됩니다.

## Ubuntu 16.04
사용자 명을 ubuntu 로, 홈 디렉토리를 /home/ubuntu 로 가정합니다.

### 1. 그래픽 라이브러리 설치
그래픽 라이브러리를 설치합니다.
```bash
$ sudo apt-get install libglu1-mesa-dev freeglut3-dev
```

### 2. python3 설치
python3 최신 버전을 잘~ 설치하세요.

### 3. boost-python 설치
boost-python 을 홈페이지에서 다운로드 받습니다. 그 후 부트스트래핑을 해 줍니다.
```bash
# python3 의 디렉토리를 잘 기입합니다.
$ ./bootstrap.sh --with-libraries=python --with-python=/usr/bin/python3.6 \
	--with-python-version=3.6 --with-python-root=/usr/local/lib/python3.6 --prefix=/home/ubuntu/boost
```

부트스트랩이 완료된 후 project-config.jam 파일을 잘 수정해야(...) 합니다.
```bash
# project-config.jam 파일에 다음 내용이 포함되어야 합니다.
import python ;
if ! [ python.configured ]
{
	    using python : 3.6 : /usr/bin/python3.6 : /usr/include/python3.6m : /usr/lib/python3.6 ;
}
...
libraries =  --with-python ;
```

빌드합니다.
```bash
$ ./b2 cxxflags=-fPIC install
```
빌드가 성공적으로 완료되면 /home/ubuntu/boost/lib/ 에 libboost_python.a 와 libboost_python.so
가 생기는데 libboost_python.so 파일을 모두 삭제합니다. 현재 빌드 중 so 파일을 참조해 버리는 문제가
있습니다.

### 4. LLVM 설치
최신 clang/lldb 를 설치합니다. 해당 문서를 참고하세요.

### 5. Skia 빌드
Skia 를 클론 받고 설정하는 방법은 동일합니다.
```bash
$ git clone 'https://chromium.googlesource.com/chromium/tools/depot_tools.git'
$ export PATH="${PWD}/depot_tools:${PATH}"
$ git clone https://skia.googlesource.com/skia.git
$ cd skia
$ python tools/git-sync-deps
```

위와 같이 사전 준비를 진행한 후 ninja 를 통해 Skia 를 Static Library
로 빌드합니다. Skia 빌드는 OSX 과 거의 비슷하나 ninja 설정에 약간의 차이가 있습니다.
```bash
$ bin/gn gen out/Static --args='is_official_build=true skia_enable_gpu=false skia_use_fontconfig=false skia_use_system_expat=false skia_use_system_freetype2=false skia_use_system_icu=false skia_use_system_libjpeg_turbo=false skia_use_system_libpng=false skia_use_system_libwebp=false skia_use_system_zlib=false cc="clang" cxx="clang++"'
$ ninja -C out/Static
```

정상적으로 빌드가 완료되면 out/Static 디렉토리에 libskia.a 파일이 생성됩니다.

# sipskia
## 빌드
sipskia 를 클론 받은 후 setup.py 파일의 상단에 있는 사용자 경로 설정 부분을 알맞게 고쳐줍니다.
그 후 라이브러리를 생성합니다.
```bash
$ python setup.py build_ext
```

정상적으로 빌드가 완료되면 libsipskia.so 파일을 확인할 수 있습니다.

## 테스트
테스트를 진행하여 올바르게 이미지가 변환되는지 확인합니다.
```bash
$ python test.py
```

output 디렉토리에 정상적으로 변환된 파일들이 생성되는지 확인합니다.

# 기타
앞서 언급한 것 처럼 별도의 pull request 나 issue 는 처리 되지 않습니다. 자유롭게 사용해 주세요.<br />
문의사항은 moonsoo.kim at nrise.net 으로 해 주시면 됩니다.
