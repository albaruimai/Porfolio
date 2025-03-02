
using System;
using System.Text;

using NHibernate;
using NHibernate.Cfg;
using NHibernate.Criterion;
using NHibernate.Exceptions;
using System.Collections.Generic;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Comentario_insertarProducto) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class ComentarioCP : BasicCP
{
public void InsertarProducto (int p_oid)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Comentario_insertarProducto) ENABLED START*/

        IComentarioCAD comentarioCAD = null;
        ComentarioCEN comentarioCEN = null;



        try
        {
                SessionInitializeTransaction ();
                comentarioCAD = new ComentarioCAD (session);
                comentarioCEN = new  ComentarioCEN (comentarioCAD);



                // Write here your custom transaction ...

                throw new NotImplementedException ("Method InsertarProducto() not yet implemented.");



                SessionCommit ();
        }
        catch (Exception ex)
        {
                SessionRollBack ();
                throw ex;
        }
        finally
        {
                SessionClose ();
        }


        /*PROTECTED REGION END*/
}
}
}
