
using System;
// Definición clase DevolucionEN
namespace Roll_n_RunGenNHibernate.EN.Roll_n_Run
{
public partial class DevolucionEN
{
/**
 *	Atributo id
 */
private int id;



/**
 *	Atributo descripcion
 */
private string descripcion;



/**
 *	Atributo motivo
 */
private Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Motivo_DevolucionEnum motivo;



/**
 *	Atributo pedido
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN pedido;



/**
 *	Atributo usuario
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario;






public virtual int Id {
        get { return id; } set { id = value;  }
}



public virtual string Descripcion {
        get { return descripcion; } set { descripcion = value;  }
}



public virtual Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Motivo_DevolucionEnum Motivo {
        get { return motivo; } set { motivo = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN Pedido {
        get { return pedido; } set { pedido = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN Usuario {
        get { return usuario; } set { usuario = value;  }
}





public DevolucionEN()
{
}



public DevolucionEN(int id, string descripcion, Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Motivo_DevolucionEnum motivo, Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN pedido, Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario
                    )
{
        this.init (Id, descripcion, motivo, pedido, usuario);
}


public DevolucionEN(DevolucionEN devolucion)
{
        this.init (Id, devolucion.Descripcion, devolucion.Motivo, devolucion.Pedido, devolucion.Usuario);
}

private void init (int id
                   , string descripcion, Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Motivo_DevolucionEnum motivo, Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN pedido, Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuario)
{
        this.Id = id;


        this.Descripcion = descripcion;

        this.Motivo = motivo;

        this.Pedido = pedido;

        this.Usuario = usuario;
}

public override bool Equals (object obj)
{
        if (obj == null)
                return false;
        DevolucionEN t = obj as DevolucionEN;
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
