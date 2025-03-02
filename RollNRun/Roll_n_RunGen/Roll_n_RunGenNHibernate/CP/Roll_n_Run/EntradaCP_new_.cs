
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



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Entrada_new_) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class EntradaCP : BasicCP
{
public Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN New_ (int p_subforo, int p_usuario, string p_texto)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Entrada_new_) ENABLED START*/

        IEntradaCAD entradaCAD = null;
        EntradaCEN entradaCEN = null;
        SubforoCAD subforoCAD = null;
        SubforoCEN subforoCEN = null;

        Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN result = null;


        try
        {
                SessionInitializeTransaction ();
                entradaCAD = new EntradaCAD (session);
                entradaCEN = new  EntradaCEN (entradaCAD);

                subforoCAD = new SubforoCAD (session);
                subforoCEN = new SubforoCEN (subforoCAD);


                int oid;
                //Initialized EntradaEN
                EntradaEN entradaEN;
                entradaEN = new EntradaEN ();

                if (p_subforo != -1) {
                        entradaEN.Subforo = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN ();
                        entradaEN.Subforo.Id = p_subforo;
                }


                if (p_usuario != -1) {
                        entradaEN.Usuario = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN ();
                        entradaEN.Usuario.Id = p_usuario;
                }

                entradaEN.Texto = p_texto;

                //Call to EntradaCAD

                oid = entradaCAD.New_ (entradaEN);

                SubforoEN subforoEN = subforoCEN.ReadOID (entradaEN.Subforo.Id);
                subforoEN.NumEntradas++;
                subforoCAD.ModifyDefault (subforoEN);


                result = entradaCAD.ReadOIDDefault (oid);



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
        return result;


        /*PROTECTED REGION END*/
}
}
}
