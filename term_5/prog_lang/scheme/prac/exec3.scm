(define times
  (lambda(x l)
    (map (lambda(a) (* x a)) l)
  )
)

(times 3 '(1 2 3 4))
(times 5 '(2 8 5))