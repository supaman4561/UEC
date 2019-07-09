(define rms
  (lambda (l)
    (sqrt (/ (apply + (map * l l)) (length l)))
  )
)

(rms '(1 2 3))
(rms '(5 1 1))