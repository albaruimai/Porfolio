
using System;
// Definición clase EntradaEN
namespace Roll_n_RunGenNHibernate.EN.Roll_n_Run
{
public partial class EntradaEN
{
/**
 *	Atributo id
 */
private int id;



/**
 *	Atributo subforo
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN subforo;



/**
 *	Atributo usuario
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario;



/**
 *	Atributo texto
 */
private string texto;



/**
 *	Atributo producto
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN producto;






public virtual int Id {
        get { return id; } set { id = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN Subforo {
        get { return subforo; } set { subforo = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN Usuario {
        get { return usuario; } set { usuario = value;  }
}



public virtual string Texto {
        get { return texto; } set { texto = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN Producto {
        get { return producto; } set { producto = value;  }
}





public EntradaEN()
{
}



public EntradaEN(int id, Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN subforo, Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario, string texto, Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN producto
                 )
{
        this.init (Id, subforo, usuario, texto, producto);
}


public EntradaEN(EntradaEN entrada)
{
        this.init (Id, entrada.Subforo, entrada.Usuario, entrada.Texto, entrada.Producto);
}

private void init (int id
                   , Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN subforo, Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario, string texto, Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN producto)
{
        this.Id = id;


        this.Subforo = subforo;

        this.Usuario = usuario;

        this.Texto = texto;

        this.Producto = producto;
}

public override bool Equals (object obj)
{
        if (obj == null)
                return false;
        EntradaEN t = obj as EntradaEN;
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
