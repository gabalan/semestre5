

(* cette tactique permet d'appliquer une élimination du forall de H par le terme t *)

Ltac forall_e H t := generalize (H t); intro.

(* Exemple *)

Example E0 : ~(forall x:nat, x <> x).
Proof.
  intro H.                                       
  forall_e H 32.
  apply H0.
  trivial.
Qed.

Section Test.
  
  Variable objet : Type.
  Variables rouge bleu vert   : objet -> Prop.
  Variables cube boule : objet-> Prop.
  
  Hypothesis col_cases : forall o, rouge o \/ bleu o \/ vert o.
  
  Hypothesis Hrb  : forall o,  ~ (rouge o /\ bleu o).
  Hypothesis Hrv  : forall o,  ~ (rouge o /\ vert o).
  Hypothesis Hbv  : forall o,  ~ (bleu  o /\ vert o).
  
  Hypothesis Hcube_boule : forall o, ~ (cube o /\ boule o).
  
  Hypothesis cube_not_blue : ~ exists o, cube o /\ bleu o.
  
  
  (* A laisser en complet *)
  Lemma L0 : forall o:objet, vert o -> ~ rouge o.
  Proof.
    intros.
    forall_e Hrv o.
    intro H1; apply H0; split; trivial. 
  Qed.
  
  Lemma Question1 : forall o, cube o -> ~ rouge o -> vert o.
  Proof.
  Admitted.
  
  Lemma Question2 : forall o, rouge o -> ~ (bleu o \/ vert o).
  Admitted.
  
  Lemma Question3 : (exists o, bleu o) -> ~ forall o, cube o.
  Admitted.
  
  Lemma Question4 : (exists o, rouge o) -> exists o1, ~bleu o1.
  Admitted.

  
  Lemma Question5 : forall c b, cube c -> boule b -> ~ b = c.
  Admitted. 
  
End Test.
