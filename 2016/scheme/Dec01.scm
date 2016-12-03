(use utils)
(define INPUT "../input/01.txt")
(define test (list
	"R5" "L5" "R5" "R3"))
	
(define (curry func arg1)  (lambda (arg) (apply func (cons arg1 (list arg)))))

(define getDirection
	(lambda(instruction)
		(string-take instruction 1)))
(define getDistance
	(lambda(instruction)
		(string->number (string-copy instruction 1))))

(define getTotalDistance
	(lambda(total distance direction)
		(abs (if (or (eq? direction 0) (eq? direction 1))
			(+ total distance)
			(- total distance)))))

(define getFacing
	(lambda(facing instruction)
		(if (and (string=? "R" (getDirection instruction)) (< facing 3))
			(+ facing 1)
			(if (string=? "R" (getDirection instruction))
				0
				(if (> facing 0)
					(- facing 1)
					3)))))

(print (map getDirection test))
(print (map getDistance test))

(print(foldl getFacing 0 test))

(print (getTotalDistance 0 (getDistance "L5") (getFacing 0 "L5")))

; n number of instructions
;  take 1..n first instructions
;   get result of (foldl getFacing 0 instructions)
;    save to list
