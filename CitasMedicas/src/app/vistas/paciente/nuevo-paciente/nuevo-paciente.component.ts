import {Component, OnInit} from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute, Router} from "@angular/router";
import {ApiService} from "../../../servicios/api/api.service";
import {PacienteInterface} from "../../../modelos/paciente.interface";

@Component({
  selector: 'app-nuevo-paciente',
  templateUrl: './nuevo-paciente.component.html',
  styleUrls: ['./nuevo-paciente.component.css']
})
export class NuevoPacienteComponent implements  OnInit {


  constructor(private activeroute:ActivatedRoute, private router:Router, private api:ApiService) {

  }
  telefono = true;
  campos = true;
  nuevoForm = new FormGroup({
    usuario: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    nombre: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    apellidos: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    clave: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    numTarjeta: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    nss: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    telefono: new FormControl<string>('', { nonNullable: true, validators: [Validators.required, Validators.pattern("[0-9 ]{9}")] }),
    direccion: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] })
  });

  ngOnInit(): void { }


  //comprobacion de los campos antes de hacer peticion
  lecturaCampos() {
    if (this.nuevoForm.controls.telefono.errors?.['pattern']) {
      this.telefono = false;
    } else {
      this.telefono = true;
    }
    if (this.nuevoForm.controls.usuario.errors?.['required'] ||
      this.nuevoForm.controls.nombre.errors?.['required'] ||
      this.nuevoForm.controls.apellidos.errors?.['required'] ||
      this.nuevoForm.controls.clave.errors?.['required'] ||
      this.nuevoForm.controls.numTarjeta.errors?.['required'] ||
      this.nuevoForm.controls.nss.errors?.['required'] ||
      this.nuevoForm.controls.telefono.errors?.['required'] ||
      this.nuevoForm.controls.direccion.errors?.['required']

    ) {
      this.campos = false;
    }
    else {
      this.campos = true;
    }

  }

  postForm(form: PacienteInterface) {
    this.lecturaCampos()
    if (this.campos && this.telefono) {
      this.api.postPaciente(form).subscribe(data =>{
        console.log(data);
        this.router.navigate(['paciente']);
      })
    }
    
  }
  atras() {
    this.router.navigate(['paciente']);
  }

}
