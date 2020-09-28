(define (square x) (* x x))

(define (sum-of-squares x y)
  (+ (square x) (square y)))

(define (abs x)
  (cond ((< x 0) (- x))
        (else x)))
