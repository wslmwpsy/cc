/ / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /  
 / /   V c k b a s e   O n l i n e   J o u r n a l   - -   F e b   2 0 0 0  
 / /   C o m p i l e s   w i t h   V i s u a l   C + +   6 . 0 ,   r u n s   o n   W i n d o w s   9 8   a n d   p r o b a b l y   N T   t o o .  
 / /  
 / /  
 # i n c l u d e   < a f x h t m l . h >  
 c l a s s   C H t m l C t r l   :   p u b l i c   C H t m l V i e w   {  
 p u b l i c :  
 	 C H t m l C t r l ( )   {   }  
 	 ~ C H t m l C t r l ( )   {   }  
  
 	 B O O L   C r e a t e W n d ( R E C T   r e c t , U I N T   n I D ,   C W n d *   p P a r e n t ) ;  
  
 	 / /   N o r m a l l y ,   C H t m l V i e w   d e s t r o y s   i t s e l f   i n   P o s t N c D e s t r o y ,  
 	 / /   b u t   w e   d o n ' t   w a n t   t o   d o   t h a t   f o r   a   c o n t r o l   s i n c e   a   c o n t r o l  
 	 / /   i s   u s u a l l y   i m p l e m e n t e d   a s   a   s t a c k   o b j e c t   i n   a   d i a l o g .  
 	 / /  
 	 v i r t u a l   v o i d   P o s t N c D e s t r o y ( )   {     }  
  
 	 / /   o v e r r i d e s   t o   b y p a s s   M F C   d o c / v i e w   f r a m e   d e p e n d e n c i e s  
 	 a f x _ m s g   v o i d   O n D e s t r o y ( ) ;  
 	 a f x _ m s g   i n t     O n M o u s e A c t i v a t e ( C W n d *   p D e s k t o p W n d ,   U I N T   n H i t T e s t ,   U I N T   m s g ) ;  
  
 	 / /   o v e r r i d e   t o   t r a p   " a p p : "   p s e u d o   p r o t o c o l  
 	 v i r t u a l   v o i d   O n B e f o r e N a v i g a t e 2 (   L P C T S T R   l p s z U R L ,  
 	 	 D W O R D   n F l a g s ,  
 	 	 L P C T S T R   l p s z T a r g e t F r a m e N a m e ,  
 	 	 C B y t e A r r a y &   b a P o s t e d D a t a ,  
 	 	 L P C T S T R   l p s z H e a d e r s ,  
 	 	 B O O L *   p b C a n c e l   ) ;  
  
 	 / /   o v e r r i d e   t o   h a n d l e   l i n k s   t o   " a p p : m u m b l e . . . " .   l p s z W h e r e   w i l l   b e   " m u m b l e "  
 	 v i r t u a l   v o i d   O n A p p C m d ( L P C T S T R   l p s z W h e r e ) ;  
  
 	 v i r t u a l   H R E S U L T   O n G e t H o s t I n f o ( D O C H O S T U I I N F O   * p I n f o ) ;  
  
 	 H W N D   m _ m e s s a g e _ h a n d l e ;       / / � � � � � � � � � � � �  
  
 	 b o o l   s e t _ m e s s a g e _ h a n d l e ( H W N D   h w n d ) ;  
  
 	 D E C L A R E _ M E S S A G E _ M A P ( ) ;  
 	 D E C L A R E _ D Y N A M I C ( C H t m l C t r l )  
 } ;  
  
 