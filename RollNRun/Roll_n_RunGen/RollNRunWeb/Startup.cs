using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(RollNRunWeb.Startup))]
namespace RollNRunWeb
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
