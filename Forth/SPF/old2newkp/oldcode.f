












: OPEN-TEMPLET.KT-FILE

	DIRPATH-STR

	S" templet.kt"	TUCK
	DIRPATH-STR	DIRPATH-LEN	+	SWAP	MOVE
	DIRPATH-LEN	+

	2DUP	CR	CR	TYPE

	R/W	OPEN-FILE
		IF
			CR	CR	." Unable to open templet.kt file."
			CLOSE-OLD-KP-FILE
			CLOSE-NEW.KP-FILE

			CR	CR	." Press any key to exit."
			CR	KEY	DROP	BYE
		THEN

	TO	TEMPLET.KT-FILE-HANDLER

; \ end OPEN-TEMPLET.KT-FILE




: CLOSE-TEMPLET.KT-FILE

	TEMPLET.KT-FILE-HANDLER	CLOSE-FILE	DROP

; \ end CLOSE-TEMPLET.KT-FILE




: CHECK-NEW.KP-EXIST

	DIRPATH-STR

	S" new.kp"	TUCK
	DIRPATH-STR	DIRPATH-LEN	+	SWAP	MOVE
	DIRPATH-STR	DIRPATH-LEN	+	+	0	SWAP	!

	FALSE	FILE-EXIST	\ File exist?
	TO	NEW.KP-EXIST-FLAG

; \ end  CHECK-NEW.KP-EXIST




: BYE-IF-KP-EXIST

	NEW.KP-EXIST-FLAG	IF
					CR	CR	." The 'new.kp' file already exist in target folder. Folder must not contain 'new.kp' file. The program will be terminated."

					CR	CR	." Press any key to exit."
					CR	KEY	DROP	BYE
				THEN

; \ end 	BYE-IF-KP-EXIST




: CHECK-TEMPLET.KT-EXIST

	DIRPATH-STR

	S" templet.kt"	TUCK
	DIRPATH-STR	DIRPATH-LEN	+	SWAP	MOVE
	DIRPATH-STR	DIRPATH-LEN	+	+	0	SWAP	!

	FALSE	FILE-EXIST	\ File exist?
	TO	TEMPLET.KP-EXIST-FLAG

; \ end CHECK-TEMPLET.KT-EXIST




: BYE-IF-TEMPLET.KP-FILE-DON'T-EXIST

	TEMPLET.KP-EXIST-FLAG
	0=	IF
			CR	CR	." The 'templet.kt' file don't exist in target folder."

			CR	CR	." Press any key to exit."
			CR	KEY	DROP	BYE
		THEN

; \ end BYE-IF-TEMPLET.KP-FILE-DON'T-EXIST




: MAKE-TEMPLET.KP-BACKUP

	CR	CR	." MAKE-TEMPLET.KP-BACKUP: Backup functionality is not implemented yet."

; \ end MAKE-TEMPLET.KP-BACKUP




(	\ Портит всё !
	0x8	OLD-KP-FILE-HANDLER	REPOSITION-FILE		DUP
	IF
		." GET-FIRST-COLORMAP: Diagnostic message: REPOSITION-FILE returned ior: "
		. ." ."
	ELSE
		DROP
	THEN
)	\ Портит всё !


	OLD-KP-FILE-HANDLER	FILE-POSITION
	CR	CR	.	.


(
	CR	CR
	HEX
	1024	0
	DO
		COLORMAP	I	+	@	.
	4	+LOOP
	DECIMAL
)


0	VALUE	MINITILE-FILE-HEADER

: CLOSE-MINITILE-FILE

	MINITILE-FILE-HEADER	CLOSE-FILE	DROP

; \ end  CLOSE-MINITILE-FILE

: CREATE-MINITILE-FILE

	DIRPATH-STR

	S" mt.tmp"	TUCK
	DIRPATH-STR	DIRPATH-LEN	+	SWAP	MOVE
	DIRPATH-STR	DIRPATH-LEN	+	+	0	SWAP	!
	FALSE

	W/O	CREATE-FILE
	0<> 	IF
			S" Unable to create 'mt.tmp' temp file."	CR	CR	TYPE
			KEY	DROP	CR	BYE
		THEN
	TO	MINITILE-FILE-HEADER

; \ end	CREATE-MINITILE-FILE




: PROCESS-CURRENT-BMP

		S" Processing: "	CR	TYPE
		2DUP	TYPE

\		OPEN-CURRENT-BMP

; \ end PROCESS-CURRENT-BMP




: FOR-EACH-LINE

	CR
	BEGIN
		READED-LINE	1024	BMP-LIST-FILE-HEADER	READ-LINE

		IF
			S" Exception : "	CR	CR	TYPE	.
			CR	CR	S" Press any key to exit."	TYPE
			KEY	DROP	CR	BYE
		THEN
	WHILE
		TO	REALY-SYMBOLS-READED

		READED-LINE	REALY-SYMBOLS-READED
		ERASE-BL-HEAD
		-TRAILING

		TO	REALY-SYMBOLS-READED
		TO	ADDR-AFTER-BL-ERASE

		ADDR-AFTER-BL-ERASE	REALY-SYMBOLS-READED	PROCESS-CURRENT-BMP

	REPEAT

; \ end FOR-EACH-LINE




: PROCESS-BMP-LIST-FILE

	CMDLN-OPTION-STR	CL-OPT-STRLEN	PARSE-"..\DIRPATH\"
	TO	DIRPATH-LEN

	DIRPATH-STR	DIRPATH-LEN
	CR	CR	TYPE	

	OPEN-BMP-LIST-FILE
	CREATE-MINITILE-FILE
	CREATE-PLOT-FILE




	S" Process file. Please wait..."	CR	CR	TYPE
	S" Or press [Ctrl]+[C] for break and exit."	CR	TYPE

	FOR-EACH-LINE


	CLOSE-PLOT-FILE
	CLOSE-MINITILE-FILE
	CLOSE-BMP-LIST-FILE

; \ end PROCESS-BMP-LIST-FILE
























