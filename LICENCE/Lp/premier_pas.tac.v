(* verifiez que votre fichier d'initialisation d'emacs 
  contient la ligne
(load-file "/usr/share/emacs/site-lisp/proofgeneral/generic/proof-site.el")
 *)


(** premiers pas en Coq *)

Section Declarations.

  Variables P Q R S T : Prop.

  Lemma imp_dist: (P -> Q -> R) -> (P -> Q) -> P -> R.
  Proof.
    intro H.
    intro H0.
    intro H1.
    apply H.
    assumption.
    apply H0.
    assumption.
  Qed.

  (* exemple de preuve d'un sequent *)

  Section S1.
    Hypothesis H : P -> Q.
    Hypothesis H0 : P -> Q -> R.

    Lemma L2 : P -> R.
    Proof.
      intro p.
      apply H0.
      assumption.
      apply H.
      assumption.
    Qed.

  End S1.

  Section About_cuts.
    Hypothesis H : P -> Q.
    Hypothesis H0 : P -> Q -> R.
    Hypothesis H1 : Q -> R -> S.
    Hypothesis H2 : Q -> R -> S -> T.

    

    (* preuve avec coupures *)

    Lemma L3 : P -> T.
      intro p.
      assert (q: Q).
      {
        apply H; assumption.
      }
      assert (r: R).
      {
        apply H0; assumption.
      }
      assert (s : S).
      {
        apply H1; assumption.
      }
      apply H2; assumption.
    Qed.



    (* preuve sans lemme (coupure) *)
    Lemma L3' : P -> T.
    Admitted.
    
  End About_cuts.


  (* Exercices 

    Reprendre les exemples vus en TD, en utilisant les tactiques 
    assumption, apply et intros

    Remplacer la commande Admitted par une preuve correcte suivie de la
    commande Qed.

   *)

  Lemma IdP : P -> P.
  Proof.
    intro p; assumption.
 Qed.


  Lemma IdPP : (P -> P) -> P -> P.
  Proof.
    intro H;assumption.
 Qed.

  (* un autre preuve *)
  Lemma IdPP' : (P -> P) -> P -> P.
  Proof.
    intros H p;apply H; assumption.
 Qed.


  Lemma imp_trans : (P -> Q) -> (Q -> R) -> P -> R.
  Proof.
    intros H H1 p.
    apply H1;apply H;assumption.
  Qed.
  
    Section proof_of_hyp_switch.
    Hypothesis H : P -> Q -> R.
    Lemma hyp_switch : Q -> P -> R.
    Proof.
      intros q p;apply H;assumption; assumption.
   Qed.
    End proof_of_hyp_switch.

  Check hyp_switch.

  Section proof_of_add_hypothesis.
    Hypothesis H : P -> R.

    Lemma add_hypothesis : P -> Q -> R.
    Proof.
      intros p q;apply H;assumption.
   Qed.

  End proof_of_add_hypothesis.

  (* prouver le sequent (P -> P -> Q) |- P -> Q  *)
  Section proof_of_sequent.
    Hypothesis H: P->P->Q.
    Lemma of_sequent:P->Q.
      Proof.
        intro p.
        apply H;assumption.
      Qed.
   End proof_of_sequent.
      
  (* meme exercice avec 
     P -> Q , P -> R , Q -> R -> T |- P -> T *)
      Section proof_of_sequent_1.
        Hypothesis H: P->Q.
        Hypothesis H1: P->R.
        Hypothesis H2:Q->R->T.
    Lemma of_sequent1:P->T.
      Proof.
        intro p;apply H2.
        apply H;assumption.
        apply H1;assumption.
      Qed.
    End proof_of_sequent_1.

   (*  Meme exercice avec 
      (P -> Q) -> R |- Q -> R*)

  Section proof_of_exercice0.
    Hypothesis H: (P->Q)->R.
    Lemma of_exercice0:Q->R.
      Proof.
        intro q;apply H.        
        intro p;assumption.
      Qed.
  End proof_of_exercice0.

(*
    Meme exercice avec  (((P->Q) -> Q) -> Q) |-  P -> Q.
 *)

  Section proof_of_exercice1.
    Hypothesis H:(((P->Q)->Q)->Q).
    Lemma of_exercice1:P->Q.
    Proof.
      intro p;apply H.
      intro q;apply q;assumption.
    Qed.
  End proof_of_exercice1.
  
      Lemma weak_Peirce : ((((P -> Q) -> P)-> P) -> Q) -> Q.
      Proof.
        intro H;apply H.
        intro H1;apply H1.
        intro p;apply H.
        intro H2;apply p.
       Qed.
        
        (* S'il reste du temps : compositions tac ; tac' 
                           tac ; trivial
                           tac ; try tac'
                           tac ; [tac1 | tac2 | ... | tacn]
                           auto.
    
   Reprendre les exemples precedents en essayant d'avoir les scrots de preuve les plus concis.
   *)

  (* Essayer de donner directement le terme de preuve des exercices precedents comme par exemple : *)

  Definition imp_dist' : (P -> Q -> R) -> (P -> Q) -> P -> R :=
    fun (H : P -> Q -> R) (H0 : P -> Q) (p: P) => H p (H0 p).


End Declarations.

