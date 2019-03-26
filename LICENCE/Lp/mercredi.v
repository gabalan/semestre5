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

  Lemma L1 : forall o:objet, ~ vert o -> ~ rouge o -> bleu o.
  Proof.
    intros.
    destruct (col_cases o).
    - contradiction.
    - destruct H1.
      + assumption.
      + contradiction.
  Qed. 


  Lemma Question1 : forall o, ~ rouge o -> bleu o \/ vert o.
  Proof.
    intros.
    forall_e col_cases o.
    destruct H0.
    left.
    contradiction.
    destruct H0.
    left.
    trivial.
    right.
    trivial.
  Qed.

  Lemma  Question2 : forall o, cube o -> vert o \/  rouge o.
  Proof.
    intros x H.
    forall_e col_cases x.
    destruct H0.
    right.
    assumption.
    destruct H0.
    assert(F: False).
    - {
        apply cube_not_blue.
        exists x.
        split;assumption.
        
      }
   
  Qed.

  Lemma Question3 : (exists b, boule b) -> ~ forall o, cube o.
  .

  Lemma Question4 : ~ exists o,  rouge o /\ bleu o.
  Admitted.

  Lemma Question5 : forall o o', rouge o -> vert o' -> ~ o = o'.
  Admitted.

  
End Test.

