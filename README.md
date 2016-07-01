# 개요
SIPSkia(Simple Image Processing by Skia) 는 Skia 기반의 간단한 이미지 resize, crop 을 수행하는
파이썬 라이브러리입니다. 모씨 앱의 카드 이미지 변환에 사용되고 있습니다. 현재는 OSX 과 Ubuntu 14.04 만
지원합니다.

# 목적
Skia 는 다른 이미지 처리 라이브러리와 비교하여 굉장히 빠른 성능과 낮은 CPU 사용률을 보입니다. 본 개발 작업을
진행하며 느낀 SKia 의 성능과 작은 노하우를 다른 분들과 공유하기 위한 목적으로 코드를 공개 하였습니다.

그런 관계로 본 프로젝트는 별도의 추가 관리는 없습니다. 어디까지나 참고용으로 사용해 주시기 바랍니다.

# 빌드 하기
## Skia 빌드
먼저 skia 홈페이지에서 skia 를 클론 받아서 설치합니다. 관련 내용은 skia 홈페이지를 참고하시면 됩니다.<br />
Ubuntu 에서 빌드할 경우 gyp 이전에 shared_library 옵션을 활성화 하여야 합니다.

```bash
$ export GYP_DEFINES="skia_shared_lib=1"
$ bin/sync_and_gyp
...
```

## boost-Python 설치
또한 [boost-Python](http://www.boost.org//) 이 필요합니다. boost-python 을 설치합니다.<br />
OSX 에서는 brew 를 이용하여 설치하는 것을 추천합니다. 굉장히 많은 시간과 귀찮음을 아낄 수 있습니다.<br />
Skia 와 마찬가지로 Ubuntu 에서 빌드할 경우 -fPIC 옵션을 줄 수 있도록 해야 합니다.

```bash
$ ./b2 cxxflags=-fPIC install
...
```

## setup.py
설치가 완료되면 setup.py 의 환경 설정 변수들을 변경한 후 다음 명령어로 라이브러리를 생성합니다.

```bash
$ python setup.py build_ext --inplace
```

# 테스트
## 기본 테스트
```bash
$ python test.py convert
```

output 디렉토리에 변환된 이미지가 저장 됩니다.

## 벤치마크 테스트
ImageMagick + Wand 와 비교하는 테스트를 확인할 수 있습니다.<br />
먼저 http://docs.wand-py.org/ 를 참고하여 ImageMagick 과 Wand 를 설치해 주세요.
```bash
$ python benchmark.py
1.52228999138
0.343165874481
```
약 4 ~ 5 배 이상 빠른 성능을 보입니다.

# 기타
앞서 언급한 것 처럼 별도의 pull request 나 issue 는 처리 되지 않습니다. 자유롭게 사용해 주세요.<br />
문의사항은 moonsoo.kim at nrise.net 으로 해 주시면 됩니다.