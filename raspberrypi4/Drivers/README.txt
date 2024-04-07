
1. 라즈비안 설치 시 config.txt 파일에 arm_64bit = 0 을 적어준다.
   이를 진행하지 않을 경우 64비트 커널로 업데이트가 된다. 

2. 'sudo su' 을 입력한다. => root 모드 진입

3. 'sudo ag-get install linux-kernels-(uname -r)' 을 입력한다. => 리눅스 커널 업데이트 

4. Drivers 폴더에서 'make'를 입력한다. => 드라이버 빌드, 드라이버 권한 변경, 드라이버 커널 등록

5. /dev/폴더에서 'ls -al'을 입력해서 드라이버의 권한을 확인한다.

6. test 폴더에서 'make'를 입력한다.

7. test 폴더에서 './test'를 입력하고 모터 드라이버의 동작을 확인한다.
