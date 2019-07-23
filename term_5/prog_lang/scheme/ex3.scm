(define ** expt)

(define diff
  (lambda (f)
    (if (list? f) (cond
                    ((equal? (car f) '+) (cons '+ (map diff (cdr f))))
                    ((equal? (car f) '-) (cons '- (map diff (cdr f))))
                    ((equal? (car f) '*) (let ((a (cadr f)) (b (caddr f)))
                                           (list '+
                                                 (list '* a (diff b))
                                                 (list '* (diff a) b))))
                    ((equal? (car f) '**) (let ((a (cadr f)) (b (caddr f)))
                                            (list '* b
                                                  (list '* (diff a)
                                                        (list '** a (- b 1)))))))
        (cond
          ((number? f) 0)
          ((equal? f 'x) 1))
    )
  )
)

(define diff2
  (lambda (f d)
    (if (list? f) (cond
                    ((equal? (car f) '+) (cons '+ (map (lambda (f) (diff2 f d)) (cdr f))))
                    ((equal? (car f) '-) (cons '- (map (lambda (f) (diff2 f d)) (cdr f))))
                    ((equal? (car f) '*) (let ((a (cadr f)) (b (caddr f)))
                                           (list '+
                                                 (list '* a (diff2 b d))
                                                 (list '* (diff2 a d) b))))
                    ((equal? (car f) '**) (let ((a (cadr f)) (b (caddr f)))
                                            (list '* b
                                                  (list '* (diff2 a d)
                                                        (list '** a (- b 1)))))))
        (cond
          ((number? f) 0)
          ((equal? f d) 1)
          (else 0))
    )
  )
)

(define tangent
  (lambda (f x)
    (let ((a ((eval `(lambda (x) ,(diff f)) (interaction-environment)) x))
          (b ((eval `(lambda (x) ,f) (interaction-environment)) x)))
      (list '+ (list '* a 'x) (- b (* a x))))
  )
)

(define getnonzero
  (lambda (lst)
    (apply append (map (lambda (x) (if (equal? x 0) '()
                                          (list x) )) lst))))

(define simple+
  (lambda (args)
    (let ((nz-lst (getnonzero args)))
      (cond ((equal? 0 (length nz-lst)) 0)
            ((equal? 1 (length nz-lst)) (car nz-lst))
            (else (cons '+ nz-lst))))))

(define simple-
  (lambda (args)
    (let ((nz-lst (getnonzero args)))
      (cond ((equal? 0 (length nz-lst)) 0)
            ((equal? 1 (length nz-lst)) (list '- (car nz-lst)))
            (else (cons '- nz-lst))))))

(define simple*
  (lambda (args)
    (let ((p (car args)) (q (cadr args)))
      (cond ((or (equal? p 0) (equal? q 0)) 0)
            ((equal? p 1) q)
            ((equal? q 1) p)
            (else (cons '* args))))))

(define simple**
  (lambda (args)
    (let ((p (car args)) (q (cadr args)))
      (cond ((equal? q 0) 1)
            ((equal? q 1) p)
            (else (cons '** args))))))

(define simple
  (lambda (f)
    (if (list? f) (cond ((equal? (car f) '+) (simple+ (map simple (cdr f))))
                        ((equal? (car f) '-) (simple- (map simple (cdr f))))
                        ((equal? (car f) '*) (simple* (map simple (cdr f))))
                        ((equal? (car f) '**) (simple** (map simple (cdr f)))))
        f )))
                                              

(diff 'x)
(diff '(+ x 5))
(diff '(+ (** x 3) (* 2 x) 4))
(diff '(** (* x 3) 2))
(diff '(* (+ x 2) (- (** x 2) x)))
(tangent '(+ (** x 3) (* -2 (** x 2)) 9) 2)
(diff2 'x 'x)
(diff2 'y 'x)
(diff2 '(+ y z) 'z)
(diff2 '(* x y) 'x)
(simple (diff '(+ x 3)))
(simple (diff '(+ (** x 2) (* 4 x) 5)))

(simple (tangent '(** x 2) 0)) 