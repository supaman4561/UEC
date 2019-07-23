(define-syntax stream-cons
  (syntax-rules ()
    ((_ x y) (cons x (delay y)))
  ))

(define-syntax stream-car
  (syntax-rules ()
    ((_ x) (car x))
  ))

(define-syntax stream-cdr
  (syntax-rules ()
    ((_ x) (force (cdr x)))
  ))

(define numbers (lambda ()
   (letrec ((stream
             (lambda (n) (stream-cons n (stream (+ n 1))))
           ))
           (stream 2))))

(define head (lambda (n L)
   (if (<= n 0)  '()
       (cons (stream-car L) (head (- n 1) (stream-cdr L)))
       )))

(define sieve (lambda (n L)
   (let ((l1 (stream-car L)))
     (if (= (modulo l1 n) 0) (sieve n (stream-cdr L))
         (stream-cons l1 (sieve n (stream-cdr L))))
   )))

(define primes (lambda ()
   (letrec ((stream
             (lambda (prm num) (stream (+ prm 1) (sieve prm num)))
           ))
           (stream 2 (numbers)))))
                              
               
(head 5 (numbers))
(head 5 (sieve 2 (numbers)))
(head 5 (primes))