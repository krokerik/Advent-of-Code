(use utils)
(define INPUT (string-split (read-all "../input/01.txt") ", "))
	
(define (take n xs)
  (if (or (zero? n) (null? xs))
      (list)
      (cons (car xs) (take (- n 1) (cdr xs)))))

(define getDirection
	(lambda(instruction)
		(string-take instruction 1)))

(define getDistance
	(lambda(instruction)
		(string->number (string-copy instruction 1))))


(define getDirDist
	(lambda(x direction distance)
		(if (eq? direction x)
			distance
			0)))

(define getFacing
	(lambda(facing instruction)
		(if (and (string=? "R" (getDirection instruction)) (< facing 3))
			(+ facing 1)
			(if (string=? "R" (getDirection instruction))
				0
				(if (> facing 0)
					(- facing 1)
					3)))))

(define totFacing
	(lambda(instructions)
		(foldl getFacing 0 instructions)))

(define unroll
	(lambda(ns pos)
		(if (eq? pos (length ns))
			(list ns)
			(cons (take pos ns) (unroll ns (+ pos 1))))))

(print (+ (abs (- (foldl + 0 (map (lambda(dir dist) (getDirDist 0 dir dist)) (map totFacing (unroll INPUT 1)) (map getDistance INPUT)))
                  (foldl + 0 (map (lambda(dir dist) (getDirDist 2 dir dist)) (map totFacing (unroll INPUT 1)) (map getDistance INPUT)))))
          (abs (- (foldl + 0 (map (lambda(dir dist) (getDirDist 1 dir dist)) (map totFacing (unroll INPUT 1)) (map getDistance INPUT)))
                  (foldl + 0 (map (lambda(dir dist) (getDirDist 3 dir dist)) (map totFacing (unroll INPUT 1)) (map getDistance INPUT)))))))