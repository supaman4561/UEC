(define myappend
  (lambda (l)
    (apply append l)
  )
)

(myappend '((1 2 3) (a b) (c d)))
