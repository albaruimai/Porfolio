
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



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Subforo_seguirSubforo) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class SubforoCP : BasicCP
{
public void SeguirSubforo (int p_oid)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Subforo_seguirSubforo) ENABLED START*/

        ISubforoCAD subforoCAD = null;
        SubforoCEN subforoCEN = null;



        try
        {
                SessionInitializeTransaction ();
                subforoCAD = new SubforoCAD (session);
                subforoCEN = new  SubforoCEN (subforoCAD);



                // Write here your custom transaction ...

                throw new NotImplementedException ("Method SeguirSubforo() not yet implemented.");



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
