import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import {HTTP_INTERCEPTORS, HttpClientModule } from "@angular/common/http";
import { AppRoutingModule, routingComponents } from './app-routing.module';
import { AppComponent } from './app.component';
import { NuevoPacienteComponent } from './vistas/paciente/nuevo-paciente/nuevo-paciente.component';
import { EditarPacienteComponent } from './vistas/paciente/editar-paciente/editar-paciente.component';
import {FormsModule, ReactiveFormsModule} from "@angular/forms";
import { MedicoComponent } from './vistas/medico/medico.component';
import { NuevoMedicoComponent } from './vistas/medico/nuevo-medico/nuevo-medico.component';
import { EditarMedicoComponent } from './vistas/medico/editar-medico/editar-medico.component';
import { CitaComponent } from './vistas/cita/cita.component';
import { EditarCitaComponent } from './vistas/cita/editar-cita/editar-cita.component';
import { NuevaCitaComponent } from './vistas/cita/nueva-cita/nueva-cita.component';
import { MenuComponent } from './vistas/menu/menu.component';
import { VerPacienteComponent } from './vistas/paciente/ver-paciente/ver-paciente.component';
import { VerMedicoComponent } from './vistas/medico/ver-medico/ver-medico.component';
import { VerCitaComponent } from './vistas/cita/ver-cita/ver-cita.component';
import { LoginComponent } from './vistas/login/login.component';
import {AuthInterceptor} from './helpers/auth.interceptor';
import { MisMedicosComponent } from './vistas/mis-medicos/mis-medicos.component';
import { MisPacientesComponent } from './vistas/mis-pacientes/mis-pacientes.component';

@NgModule({
  declarations: [
    AppComponent,
    routingComponents,
    NuevoPacienteComponent,
    EditarPacienteComponent,
    MedicoComponent,
    NuevoMedicoComponent,
    EditarMedicoComponent,
    CitaComponent,
    EditarCitaComponent,
    NuevaCitaComponent,
    MenuComponent,
    VerPacienteComponent,
    VerMedicoComponent,
    VerCitaComponent,
    LoginComponent,
    MisMedicosComponent,
    MisPacientesComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    ReactiveFormsModule,
    FormsModule
  ],
  providers: [
    {
      provide: HTTP_INTERCEPTORS, useClass: AuthInterceptor, multi: true
    }
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
