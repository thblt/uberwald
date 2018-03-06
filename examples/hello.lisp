(defn hello [ (who . "world") (greeting . "Hello,") ]
  "Say hello to WHO."
  (print (format "%s, %s!" greeting who)))
