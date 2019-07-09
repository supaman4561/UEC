(define numlist
  (lambda (x)
    (if (<= x 0) '()
                 (cons x (numlist (- x 1)))
    )
  )
)

(numlist 10)
(numlist 1)
(numlist -1)