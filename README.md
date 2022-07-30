# ATMega128_Project
## 아두이노 우노 보드를 이용해 진행한 auto tracking fan을 수정한 프로젝트입니다.
### 기능
#### 1. atmega128A, atmega328P 보드 통신
- USART0 : 디버깅 용, putty 출력.  
- USART1 : 아두이노 우노 보드 시리얼 통신 전용.  
  - 온습도 센서 값 > DC 모터 속도 조절  
  - 초음파 센서 L,R > 서보 모터 각도 조절  
#### 2. auto tracking mode
- 초음파 센서 2개 이용 (UNO)  
- 타이머 이용 서보 모터 컨트롤 (ATMEGA)  
#### 3. Start / Stop
- 모터 제어 : L293D 모터드라이버, dc모터  
  - 온도, 습도에 따라 속도 조절
#### 4. Timer
- fast PWM mode  
  1. 서보 모터  
    OC 인터럽트 : r, l count 값 조절로 안정적인 서보 모터 각도 제어  
  2. dc 모터  
    OCR 값 조절로 펄스 폭 변경해 dc모터 속도 제어  
#### 5. LCD
- LCD를 이용하기 위해 init, gotoXY, write, clear 등 함수 설정  
- 온도, 습도, 거리L, 거리R 표시  
### 추가할 내용
#### 1. Tracking
- 제대로 된 tracking을 위해 영상 처리나 point to point 거리를 측정할 센서 추가
- 2축 제어 추가
#### 2. 통신
- Bluetooth 이용
### 일정
22.07.29 arduino, atmega 기본 기능 완성
