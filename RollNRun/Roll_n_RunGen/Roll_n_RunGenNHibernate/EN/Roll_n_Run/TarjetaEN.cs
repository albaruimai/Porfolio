
using System;
// Definición clase TarjetaEN
namespace Roll_n_RunGenNHibernate.EN.Roll_n_Run
{
public partial class TarjetaEN
{
/**
 *	Atributo titular
 */
private string titular;



/**
 *	Atributo numero
 */
private string numero;



/**
 *	Atributo cvv
 */
private string cvv;



/**
 *	Atributo fechaCad
 */
private Nullable<DateTime> fechaCad;



/**
 *	Atributo id
 */
private int id;



/**
 *	Atributo usuario
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario;



/**
 *	Atributo pedido
 */
private System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN> pedido;






public virtual string Titular {
        get { return titular; } set { titular = value;  }
}



public virtual string Numero {
        get { return numero; } set { numero = value;  }
}



public virtual string Cvv {
        get { return cvv; } set { cvv = value;  }
}



public virtual Nullable<DateTime> FechaCad {
        get { return fechaCad; } set { fechaCad = value;  }
}



public virtual int Id {
        get { return id; } set { id = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN Usuario {
        get { return usuario; } set { usuario = value;  }
}



public virtual System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN> Pedido {
        get { return pedido; } set { pedido = value;  }
}





public TarjetaEN()
{
        pedido = new System.Collections.Generic.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN>();
}



public TarjetaEN(int id, string titular, string numero, string cvv, Nullable<DateTime> fechaCad, Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario, System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN> pedido
                 )
{
        this.init (Id, titular, numero, cvv, fechaCad, usuario, pedido);
}


public TarjetaEN(TarjetaEN tarjeta)
{
        this.init (Id, tarjeta.Titular, tarjeta.Numero, tarjeta.Cvv, tarjeta.FechaCad, tarjeta.Usuario, tarjeta.Pedido);
}

private void init (int id
                   , string titular, string numero, string cvv, Nullable<DateTime> fechaCad, Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario, System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN> pedido)
{
        this.Id = id;


        this.Titular = titular;

        this.Numero = numero;

        this.Cvv = cvv;

        this.FechaCad = fechaCad;

        this.Usuario = usuario;

        this.Pedido = pedido;
}

public override bool Equals (object obj)
{
        if (obj == null)
                return false;
        TarjetaEN t = obj as TarjetaEN;
        if (t == null)
                return false;
        if (Id.Equals (t.Id))
                return true;
        else
                return false;
}

public override int GetHashCode ()
{
        int hash = 13;

        hash += this.Id.GetHashCode ();
        return hash;
}
}
}
