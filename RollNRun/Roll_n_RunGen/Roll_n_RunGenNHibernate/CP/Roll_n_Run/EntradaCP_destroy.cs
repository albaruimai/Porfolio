
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



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Entrada_destroy) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class EntradaCP : BasicCP
{
public void Destroy (int p_Entrada_OID)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Entrada_destroy) ENABLED START*/

        IEntradaCAD entradaCAD = null;
        EntradaCEN entradaCEN = null;
        SubforoEN subforoEN = null;
        SubforoCAD subforoCAD = null;
        SubforoCEN subforoCEN = null;




        try
        {
                SessionInitializeTransaction ();
                entradaCAD = new EntradaCAD (session);
                entradaCEN = new  EntradaCEN (entradaCAD);

                subforoCAD = new SubforoCAD (session);
                subforoCEN = new SubforoCEN (subforoCAD);

                EntradaEN entradaEN = entradaCEN.ReadOID (p_Entrada_OID);

                subforoEN = subforoCEN.ReadOID (entradaEN.Subforo.Id);
                subforoEN.NumEntradas--;
                subforoCAD.ModifyDefault (subforoEN);


                entradaCAD.Destroy (p_Entrada_OID);


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
