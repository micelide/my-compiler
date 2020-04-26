# recursive-descent parser
⟨Program⟩ ::= ⟨StmtList⟩ . 
⟨StmtList⟩ ::= ⟨Stmt⟩ ⟨NextStmt⟩
⟨NextStmt⟩ ::= ; ⟨StmtList⟩ | ε
⟨Stmt⟩ ::= ⟨Assign⟩ | ⟨Print⟩ 
⟨Assign⟩ ::= ⟨Id⟩ = ⟨Expr⟩
⟨Print⟩ ::= ! ⟨Id⟩
⟨Expr⟩ ::=  + ⟨Expr ⟩ ⟨Expr ⟩ 
            | - ⟨Expr ⟩ ⟨Expr ⟩ 
            | * ⟨Expr ⟩ ⟨Expr ⟩ 
            | / ⟨Expr ⟩ ⟨Expr ⟩ 
            | ⟨Id⟩
            | ⟨Const⟩
⟨Id⟩ ::= a|b|c
⟨Const⟩ ::= 0|1|2|3|4|5|6|7|8|9
