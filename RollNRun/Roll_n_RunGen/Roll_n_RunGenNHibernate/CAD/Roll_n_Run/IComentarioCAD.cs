
using System;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial interface IComentarioCAD
{
ComentarioEN ReadOIDDefault (int id
                             );

void ModifyDefault (ComentarioEN comentario);

System.Collections.Generic.IList<ComentarioEN> ReadAllDefault (int first, int size);



int New_ (ComentarioEN comentario);

void Modify (ComentarioEN comentario);


void Destroy (int id
              );


ComentarioEN ReadOID (int id
                      );


System.Collections.Generic.IList<ComentarioEN> ReadAll (int first, int size);



System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ComentarioEN> GetComentariosSubforo ();
}
}
