<파이썬 - C 모듈 연결>

셋업 실행하기 
python ex02_setup.py build_ext --inplace

셋업파일이 DLL(pyd) 파일을 만들어 줍니다.

python 인터프리터에서 실행하기

import _ex02
print(_ex02.__doc__)
_ex02.hello()

<텐서플로우>
1. 가상환경에서 설치
  pip install tensorflow
  pip install tensorflow-gpu