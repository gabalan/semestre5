Section Negation.
  Variables P Q S: Prop.

  (* Executez cette preuve en essayant de comprendre le sens de chacune des nouvelles tactiques utilisées. *)
  Lemma absurde_exemple: P -> ~P -> S.
  Proof.
    intros p np.
    unfold not in np.
    assert(F: False).
    {  apply np; assumption.
    }
    destruct F.
  Qed.
  
  Lemma triple_neg_e : ~~~P -> ~P.
  Proof.
     intros H. 
     intro H0.
     apply H.
     intro H1.
     apply H1; trivial.
   Restart.
   unfold not.
   auto.
   Qed.


    (* Remplacer les tactiques automatiques "auto" et  "tauto" par une preuve 
       trouvee interactivement par vous meme personnellement *)
  Lemma absurde: (P -> Q) -> (P -> ~Q) -> (P -> S).
  Proof.
    intro H.
    intro H1.
    intro H2.
    unfold not in H1.
    assert(F:False).
    {
      apply H1.
      assumption.
      apply H.
      assumption.
    }
    destruct F.
  Qed.




  Lemma triple_abs: ~P -> ~~~P.
  Proof.
    intro a.
    intro b.
    unfold not in a.
    unfold not in b.
    assert(F:False).
    {
      apply b.
      assumption.
    }
    destruct F.
  Qed. 
  
  Lemma absurd' : (~P -> P) -> ~~P.
  Proof.
    intro x.
    unfold not in x.
    intro y.
    unfold not in y.
    apply y.
    apply x.
    assumption.
  Qed.

  Definition PEIRCE  := ((P -> Q) -> P) -> P.

  

  Lemma Peirce_2 : ~~ PEIRCE.
  Proof.
    unfold PEIRCE.
    unfold not.
    intro x.
    apply x.
    intro a.
    apply a.
    intro b.
    assert(F:False).
   {
     apply x.
     intro c.
     trivial.
   }
   destruct F.
  Qed.

End Negation.



(*  Logique propositionnelle intuitionniste *)

Section LJ.
 Variables P Q R S T : Prop.
 (*  Tactiques pour la conjonction 

    Introduction : pour prouver A /\ B : split
    Elimination : destruct H, si H : A /\ B 
                  variante : destruct H as [H1 H2].

  *)
 Lemma and_comm : P /\ Q -> Q /\ P.
 Proof.
   intro H.
   destruct H as [H0 H1].
   split; trivial. 
 Qed.


 (* tactiques pour la disjonction 
    Introduction:
     pour prouver A \/ B a partir de A : left
     pour prouver A \/ B a partir de B : right

    Elimination:
     preuve par cas : destruct H, si H: A \/ B
                      variante : destruct H as [H1 | H2]

  *)

  Lemma or_not : P \/ Q -> ~P -> Q.
  Proof.
   intros H H0.     
   destruct H.     
   - assert False.
     {
       apply H0; trivial.
     }
     destruct H1.
    -    trivial. 
   Qed.

   (*  equivalence logique :
       A <-> B se transforme en (A -> B) /\ (B -> A).
       donc split, destruct, unfold iff marchent
    *)

  Lemma iff_comm : (P <-> Q) -> (Q <-> P).
  Proof.
    intro H.
     destruct H.
     split.
     assumption.
     assumption.
  Qed.

  (* la regle de remplacement est implantée en Coq *)
  Require Import Setoid.
  
  Lemma L1 : (P <-> Q) -> ~(Q <-> ~P).
  Proof.  
     intro H.
     rewrite H.  (* Variantes : rewrite <- H 
                                rewrite H in H0
                                etc.
                  *)
     
     intro H0;destruct H0.
     assert (~Q).
     { intro H2.
       apply H0; assumption.
     }
     apply H2;auto.
  Qed.


  


  (* Exercice : remplacer tauto par des vraies preuves interactives *)
  (*  Exercices de la feuille 2 *)

  Lemma and_false : P /\ False -> False.
  Proof. 
    intro h.
    destruct h.
    assumption.
   Qed.

  Lemma and_assoc : (P /\ Q) /\ R <-> P /\ (Q /\ R).
  Proof.
    split.
    intro a.
    destruct a.
    destruct H.
    split .
    assumption.
    split . 
    assumption.
    assumption.
    intro x.
    destruct x.
    destruct H0.
    split .
    split.
    assumption.
    assumption.
    assumption.
  Qed.

  Lemma or2imp: ~ P \/ Q -> P -> Q.
  Proof.
    intro a.
    unfold not in a.
    intro b.
    destruct a.
    -assert False.
    {
      apply H.
      assumption.
    }
    destruct H0.
    -assumption.
  Qed.   

  Lemma and_or_dist : P /\ (Q \/ R) <-> P /\ Q \/ P /\ R.
  Proof.
    split .
    intros.
    destruct H.
    destruct H0.
    left.
    split;assumption.
    right.
    split;assumption.
    intros.
    destruct H.
    split.
    destruct H.
    assumption.
    left.
    destruct H.
    assumption.
    destruct H.
    split.
    assumption.
    right.
    assumption.
  Qed.

   Lemma and_not_not_impl: P /\ ~ Q -> ~(P -> Q).
   Proof.
     intro H.
     unfold not in H.
     intro.
     destruct H.
     apply H1.
     apply H0.
     assumption.
   Qed.

   Lemma de_morgan1 : ~ (P \/ Q) -> ~P /\ ~Q.
   Proof.
     unfold not.
     intro H.
     split .
     intro A.
     apply H.
     left.
     assumption.
     intro B.
     destruct H.
     right.
     assumption.
   Qed.

End LJ.


(*  Logique classique

On executera  les 4 commandes suivantes 

 *)


Definition EXM :=   forall A:Prop, A \/ ~A.

Ltac add_exm  A :=
  let hname := fresh "exm" in
  assert(hname : A \/ ~A);auto.

Section LK.

  Hypothesis  exm :  EXM.

  (* 
   Pour ajouter une instance du tiers-exclu de la forme  A \/ ~A 
   il suffit d'exécuter la commande "add_exm A"
   *)

  
   Variables P Q R S T : Prop.



  Lemma double_neg : ~~ P -> P.
  Proof.
    intro H.
    add_exm  P.
    destruct exm0.
     assumption.
     assert(F:False).
     apply H.
     assumption.
     destruct F.
  Qed.


  Lemma de_morgan : ~ (~ P /\ ~ Q) <-> P \/ Q.
  Proof.
  Admitted.

  Lemma not_impl_or : ~(P -> Q) <-> P /\ ~ Q.
  Proof.
  Admitted.


  Lemma exm_e : (P -> Q) -> (~P -> Q) -> Q.
  Proof.
   intro a.
   intro b.
   add_exm Q.
   destruct exm0.
   assumption.
   apply b.
   intro c.
   apply H.
   apply a.
   assumption.
  Qed.
   Lemma exo_18 : (~ P -> P) -> P.
  Proof.
    intro h.
    add_exm P.
    destruct exm0.
    assumption.
    apply h.
    assumption.
  Qed.
  
  Lemma exo19 : (P -> Q) \/ (Q -> P).
  Proof.
  Admitted.

  Lemma imp_translation : (P -> Q) <-> ~P \/ Q.
  Proof.
  Admitted.

  Lemma Peirce : (( P -> Q) -> P) -> P.
  Proof.
    .
  Admitted.


  End LK.

About double_neg.


  