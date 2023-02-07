   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  17                     	bsct
  18  0000               _targetAdcCount:
  19  0000 00            	dc.b	0
  20  0001               _programStatus:
  21  0001 00            	dc.b	0
  22  0002               _programTime:
  23  0002 00000000      	dc.l	0
  65                     ; 32 void uartTransmit(uint8_t data){
  67                     .text:	section	.text,new
  68  0000               _uartTransmit:
  70  0000 88            	push	a
  71       00000000      OFST:	set	0
  74  0001               L13:
  75                     ; 33 	while(!UART1_GetFlagStatus(UART1_FLAG_TXE));
  77  0001 ae0080        	ldw	x,#128
  78  0004 cd0000        	call	_UART1_GetFlagStatus
  80  0007 4d            	tnz	a
  81  0008 27f7          	jreq	L13
  82                     ; 34 	UART1_SendData8(data);
  84  000a 7b01          	ld	a,(OFST+1,sp)
  85  000c cd0000        	call	_UART1_SendData8
  87                     ; 35 }
  90  000f 84            	pop	a
  91  0010 81            	ret
 117                     ; 37 @far @interrupt void uartReceive(void)	{
 119                     .text:	section	.text,new
 120  0000               f_uartReceive:
 122  0000 8a            	push	cc
 123  0001 84            	pop	a
 124  0002 a4bf          	and	a,#191
 125  0004 88            	push	a
 126  0005 86            	pop	cc
 127  0006 3b0002        	push	c_x+2
 128  0009 be00          	ldw	x,c_x
 129  000b 89            	pushw	x
 130  000c 3b0002        	push	c_y+2
 131  000f be00          	ldw	x,c_y
 132  0011 89            	pushw	x
 135                     ; 38 	UART1_ClearITPendingBit(UART1_IT_RXNE);
 137  0012 ae0255        	ldw	x,#597
 138  0015 cd0000        	call	_UART1_ClearITPendingBit
 140                     ; 39 	uartData=UART1_ReceiveData8();
 142  0018 cd0000        	call	_UART1_ReceiveData8
 144  001b b701          	ld	_uartData,a
 145                     ; 40 }
 148  001d 85            	popw	x
 149  001e bf00          	ldw	c_y,x
 150  0020 320002        	pop	c_y+2
 151  0023 85            	popw	x
 152  0024 bf00          	ldw	c_x,x
 153  0026 320002        	pop	c_x+2
 154  0029 80            	iret
 185                     .const:	section	.text
 186  0000               L21:
 187  0000 00000258      	dc.l	600
 188  0004               L41:
 189  0004 00000190      	dc.l	400
 190  0008               L61:
 191  0008 000002bc      	dc.l	700
 192                     ; 42 @far @interrupt void tim1Update(void)	{
 193                     .text:	section	.text,new
 194  0000               f_tim1Update:
 196  0000 8a            	push	cc
 197  0001 84            	pop	a
 198  0002 a4bf          	and	a,#191
 199  0004 88            	push	a
 200  0005 86            	pop	cc
 201  0006 3b0002        	push	c_x+2
 202  0009 be00          	ldw	x,c_x
 203  000b 89            	pushw	x
 204  000c 3b0002        	push	c_y+2
 205  000f be00          	ldw	x,c_y
 206  0011 89            	pushw	x
 207  0012 be02          	ldw	x,c_lreg+2
 208  0014 89            	pushw	x
 209  0015 be00          	ldw	x,c_lreg
 210  0017 89            	pushw	x
 213                     ; 43 	TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
 215  0018 a601          	ld	a,#1
 216  001a cd0000        	call	_TIM1_ClearITPendingBit
 218                     ; 45 	adcData = (uint8_t)(ADC1_GetConversionValue()>>2);
 220  001d cd0000        	call	_ADC1_GetConversionValue
 222  0020 54            	srlw	x
 223  0021 54            	srlw	x
 224  0022 9f            	ld	a,xl
 225  0023 b700          	ld	_adcData,a
 226                     ; 46 	if(adcData >= TARGETADC) {
 228  0025 b600          	ld	a,_adcData
 229  0027 a173          	cp	a,#115
 230  0029 250a          	jrult	L36
 231                     ; 47 		if(targetAdcCount < TARGETADCCOUNTMAX) {
 233  002b b600          	ld	a,_targetAdcCount
 234  002d a10a          	cp	a,#10
 235  002f 240a          	jruge	L76
 236                     ; 48 			targetAdcCount++;
 238  0031 3c00          	inc	_targetAdcCount
 239  0033 2006          	jra	L76
 240  0035               L36:
 241                     ; 52 		if(targetAdcCount > 0) {
 243  0035 3d00          	tnz	_targetAdcCount
 244  0037 2702          	jreq	L76
 245                     ; 53 			targetAdcCount--;
 247  0039 3a00          	dec	_targetAdcCount
 248  003b               L76:
 249                     ; 56 	uartTransmit(adcData);
 251  003b b600          	ld	a,_adcData
 252  003d cd0000        	call	_uartTransmit
 254                     ; 57 	uartTransmit(targetAdcCount);
 256  0040 b600          	ld	a,_targetAdcCount
 257  0042 cd0000        	call	_uartTransmit
 259                     ; 58 	switch(programStatus) {
 261  0045 b601          	ld	a,_programStatus
 263                     ; 86 		break;
 264  0047 4d            	tnz	a
 265  0048 270a          	jreq	L54
 266  004a 4a            	dec	a
 267  004b 2739          	jreq	L74
 268  004d 4a            	dec	a
 269  004e 2765          	jreq	L15
 270  0050 ace600e6      	jpf	L57
 271  0054               L54:
 272                     ; 59 		case STARTING:
 272                     ; 60 			programTime++;
 274  0054 ae0002        	ldw	x,#_programTime
 275  0057 a601          	ld	a,#1
 276  0059 cd0000        	call	c_lgadc
 278                     ; 61 			if(programTime >= STARTINGTIME) {
 280  005c ae0002        	ldw	x,#_programTime
 281  005f cd0000        	call	c_ltor
 283  0062 ae0000        	ldw	x,#L21
 284  0065 cd0000        	call	c_lcmp
 286  0068 257c          	jrult	L57
 287                     ; 62 				programTime = 0;
 289  006a ae0000        	ldw	x,#0
 290  006d bf04          	ldw	_programTime+2,x
 291  006f ae0000        	ldw	x,#0
 292  0072 bf02          	ldw	_programTime,x
 293                     ; 63 				if(targetAdcCount == TARGETADCCOUNTMAX) {
 295  0074 b600          	ld	a,_targetAdcCount
 296  0076 a10a          	cp	a,#10
 297  0078 2606          	jrne	L101
 298                     ; 64 					programStatus = RESTING;
 300  007a 35020001      	mov	_programStatus,#2
 302  007e 2066          	jra	L57
 303  0080               L101:
 304                     ; 67 					programStatus = WORKING;
 306  0080 35010001      	mov	_programStatus,#1
 307  0084 2060          	jra	L57
 308  0086               L74:
 309                     ; 71 		case WORKING:
 309                     ; 72 			GPIO_WriteLow(SWITCH_PORT, SWITCH_PIN);
 311  0086 4b10          	push	#16
 312  0088 ae500f        	ldw	x,#20495
 313  008b cd0000        	call	_GPIO_WriteLow
 315  008e 84            	pop	a
 316                     ; 73 			programTime++;
 318  008f ae0002        	ldw	x,#_programTime
 319  0092 a601          	ld	a,#1
 320  0094 cd0000        	call	c_lgadc
 322                     ; 74 			if(programTime >= WORKINGTIME) {
 324  0097 ae0002        	ldw	x,#_programTime
 325  009a cd0000        	call	c_ltor
 327  009d ae0004        	ldw	x,#L41
 328  00a0 cd0000        	call	c_lcmp
 330  00a3 2541          	jrult	L57
 331                     ; 75 				programTime = 0;
 333  00a5 ae0000        	ldw	x,#0
 334  00a8 bf04          	ldw	_programTime+2,x
 335  00aa ae0000        	ldw	x,#0
 336  00ad bf02          	ldw	_programTime,x
 337                     ; 76 				programStatus = RESTING;
 339  00af 35020001      	mov	_programStatus,#2
 340  00b3 2031          	jra	L57
 341  00b5               L15:
 342                     ; 79 		case RESTING:
 342                     ; 80 			GPIO_WriteHigh(SWITCH_PORT, SWITCH_PIN);
 344  00b5 4b10          	push	#16
 345  00b7 ae500f        	ldw	x,#20495
 346  00ba cd0000        	call	_GPIO_WriteHigh
 348  00bd 84            	pop	a
 349                     ; 81 			programTime++;
 351  00be ae0002        	ldw	x,#_programTime
 352  00c1 a601          	ld	a,#1
 353  00c3 cd0000        	call	c_lgadc
 355                     ; 82 			if(programTime >= RESTINGTIME && targetAdcCount == 0) {
 357  00c6 ae0002        	ldw	x,#_programTime
 358  00c9 cd0000        	call	c_ltor
 360  00cc ae0008        	ldw	x,#L61
 361  00cf cd0000        	call	c_lcmp
 363  00d2 2512          	jrult	L57
 365  00d4 3d00          	tnz	_targetAdcCount
 366  00d6 260e          	jrne	L57
 367                     ; 83 				programTime = 0;
 369  00d8 ae0000        	ldw	x,#0
 370  00db bf04          	ldw	_programTime+2,x
 371  00dd ae0000        	ldw	x,#0
 372  00e0 bf02          	ldw	_programTime,x
 373                     ; 84 				programStatus = WORKING;
 375  00e2 35010001      	mov	_programStatus,#1
 376  00e6               L57:
 377                     ; 88 }
 380  00e6 85            	popw	x
 381  00e7 bf00          	ldw	c_lreg,x
 382  00e9 85            	popw	x
 383  00ea bf02          	ldw	c_lreg+2,x
 384  00ec 85            	popw	x
 385  00ed bf00          	ldw	c_y,x
 386  00ef 320002        	pop	c_y+2
 387  00f2 85            	popw	x
 388  00f3 bf00          	ldw	c_x,x
 389  00f5 320002        	pop	c_x+2
 390  00f8 80            	iret
 427                     ; 90 main() {
 429                     .text:	section	.text,new
 430  0000               _main:
 434                     ; 91 	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1|CLK_PRESCALER_CPUDIV1);
 436  0000 a680          	ld	a,#128
 437  0002 cd0000        	call	_CLK_HSIPrescalerConfig
 439                     ; 93 	UART1_DeInit();
 441  0005 cd0000        	call	_UART1_DeInit
 443                     ; 94 	UART1_Init(	57600,
 443                     ; 95 							UART1_WORDLENGTH_8D,
 443                     ; 96 							UART1_STOPBITS_1,
 443                     ; 97 							UART1_PARITY_NO,
 443                     ; 98 							UART1_SYNCMODE_CLOCK_DISABLE,
 443                     ; 99 							UART1_MODE_TXRX_ENABLE);
 445  0008 4b0c          	push	#12
 446  000a 4b80          	push	#128
 447  000c 4b00          	push	#0
 448  000e 4b00          	push	#0
 449  0010 4b00          	push	#0
 450  0012 aee100        	ldw	x,#57600
 451  0015 89            	pushw	x
 452  0016 ae0000        	ldw	x,#0
 453  0019 89            	pushw	x
 454  001a cd0000        	call	_UART1_Init
 456  001d 5b09          	addw	sp,#9
 457                     ; 100 	UART1_ITConfig(	UART1_IT_RXNE, ENABLE);
 459  001f 4b01          	push	#1
 460  0021 ae0255        	ldw	x,#597
 461  0024 cd0000        	call	_UART1_ITConfig
 463  0027 84            	pop	a
 464                     ; 101 	UART1_Cmd(ENABLE);
 466  0028 a601          	ld	a,#1
 467  002a cd0000        	call	_UART1_Cmd
 469                     ; 103 	TIM1_DeInit();
 471  002d cd0000        	call	_TIM1_DeInit
 473                     ; 104 	TIM1_TimeBaseInit(	16000,
 473                     ; 105 											TIM1_COUNTERMODE_UP,
 473                     ; 106 											1000,
 473                     ; 107 											0);
 475  0030 4b00          	push	#0
 476  0032 ae03e8        	ldw	x,#1000
 477  0035 89            	pushw	x
 478  0036 4b00          	push	#0
 479  0038 ae3e80        	ldw	x,#16000
 480  003b cd0000        	call	_TIM1_TimeBaseInit
 482  003e 5b04          	addw	sp,#4
 483                     ; 108 	TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
 485  0040 ae0101        	ldw	x,#257
 486  0043 cd0000        	call	_TIM1_ITConfig
 488                     ; 109 	TIM1_Cmd(ENABLE);
 490  0046 a601          	ld	a,#1
 491  0048 cd0000        	call	_TIM1_Cmd
 493                     ; 111 	ADC1_DeInit();
 495  004b cd0000        	call	_ADC1_DeInit
 497                     ; 112 	ADC1_Init(	ADC1_CONVERSIONMODE_CONTINUOUS,
 497                     ; 113 							ADC1_CHANNEL_3,
 497                     ; 114 							ADC1_PRESSEL_FCPU_D18,
 497                     ; 115 							ADC1_EXTTRIG_TIM,
 497                     ; 116 							DISABLE,
 497                     ; 117 							ADC1_ALIGN_RIGHT,
 497                     ; 118 							ADC1_SCHMITTTRIG_CHANNEL3,
 497                     ; 119 							DISABLE);
 499  004e 4b00          	push	#0
 500  0050 4b03          	push	#3
 501  0052 4b08          	push	#8
 502  0054 4b00          	push	#0
 503  0056 4b00          	push	#0
 504  0058 4b70          	push	#112
 505  005a ae0103        	ldw	x,#259
 506  005d cd0000        	call	_ADC1_Init
 508  0060 5b06          	addw	sp,#6
 509                     ; 120 	ADC1_Cmd(ENABLE);
 511  0062 a601          	ld	a,#1
 512  0064 cd0000        	call	_ADC1_Cmd
 514                     ; 121 	ADC1_StartConversion();
 516  0067 cd0000        	call	_ADC1_StartConversion
 518                     ; 124 	GPIO_Init(SWITCH_PORT, SWITCH_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
 520  006a 4bf0          	push	#240
 521  006c 4b10          	push	#16
 522  006e ae500f        	ldw	x,#20495
 523  0071 cd0000        	call	_GPIO_Init
 525  0074 85            	popw	x
 526                     ; 126 	enableInterrupts();
 529  0075 9a            rim
 531  0076               L121:
 532                     ; 128 	while (1);
 534  0076 20fe          	jra	L121
 594                     	xdef	_main
 595                     	xdef	f_tim1Update
 596                     	xdef	f_uartReceive
 597                     	xdef	_uartTransmit
 598                     	xdef	_programTime
 599                     	xdef	_programStatus
 600                     	xdef	_targetAdcCount
 601                     	switch	.ubsct
 602  0000               _adcData:
 603  0000 00            	ds.b	1
 604                     	xdef	_adcData
 605  0001               _uartData:
 606  0001 00            	ds.b	1
 607                     	xdef	_uartData
 608                     	xref	_UART1_ClearITPendingBit
 609                     	xref	_UART1_GetFlagStatus
 610                     	xref	_UART1_SendData8
 611                     	xref	_UART1_ReceiveData8
 612                     	xref	_UART1_ITConfig
 613                     	xref	_UART1_Cmd
 614                     	xref	_UART1_Init
 615                     	xref	_UART1_DeInit
 616                     	xref	_TIM1_ClearITPendingBit
 617                     	xref	_TIM1_ITConfig
 618                     	xref	_TIM1_Cmd
 619                     	xref	_TIM1_TimeBaseInit
 620                     	xref	_TIM1_DeInit
 621                     	xref	_GPIO_WriteLow
 622                     	xref	_GPIO_WriteHigh
 623                     	xref	_GPIO_Init
 624                     	xref	_CLK_HSIPrescalerConfig
 625                     	xref	_ADC1_GetConversionValue
 626                     	xref	_ADC1_StartConversion
 627                     	xref	_ADC1_Cmd
 628                     	xref	_ADC1_Init
 629                     	xref	_ADC1_DeInit
 630                     	xref.b	c_lreg
 631                     	xref.b	c_x
 632                     	xref.b	c_y
 652                     	xref	c_lcmp
 653                     	xref	c_ltor
 654                     	xref	c_lgadc
 655                     	end
