(ns Dec01)
(defn convert [x] (map #(if (= \( %) 1 -1) x))
(defn part1 [x] (apply + (convert x)))
(defn part2 [x] (->> x (convert) (reductions +) (take-while (partial <= -1)) (count)))

(use 'clojure.java.io)
(with-open [rdr (reader "../input/01.txt")]
 (doseq [line (line-seq rdr)]
  (println (part1 (seq line)))
  (println (part2 (seq line)))))