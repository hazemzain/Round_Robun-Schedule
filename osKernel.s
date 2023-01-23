			AREA |.text|, CODE, READONLY, ALIGN=2
			THUMB
			EXTERN currentPtr
			EXPORT SysTick_Handler
			EXPORT osSchedulerLaunch
SysTick_Handler
	CPSID	I ;disable all interrupt
	PUSH	{R4-R11} ;SAVE R4,R5,R6,R7,R8,R9,R10,R11
	LDR R0,=currentPtr ;R0 POINT TO CURRENT PTR
	LDR R1,[R0] ;R1=CURRENTPTR ,R1 have address of task 0 
	STR SP,[R1]
	LDR R1,[R1,#4] ; LOAD THE SECEND TCB INTO R1 R1=CURRNTPTR+4(CURNETPTR->NEXT)
	STR R1,[R0] ;CURRNTPTR=R1
	LDR SP,[R1] ; SP=CURRENTPTR->NEXT
	POP {R4-R11}
	CPSIE	I ;ENABLE INTERRUPT
	BX 		LR
osSchedulerLaunch
	LDR R0,=currentPtr ;R0 POINT TO CURRENT PTR
	LDR R2,[R0] ;R2 =CurrenntPtr
	LDR SP,[R2] ;sp=current pt->stack
	POP {R4-R11} ;pop R4,R5,R6,R7,R8,R9,R10,R11
	POP {R0-R3} ;POP R0,R1,R2,R3
	POP {R12}
	ADD SP,SP,#4
	POP {LR}
	ADD SP,SP,#4
	CPSIE	I ;ENABLE INTERRUPT
	BX 		LR
	
	ALIGN
	END