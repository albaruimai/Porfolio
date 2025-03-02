import {Component, OnInit} from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute, Router} from "@angular/router";
import {ApiService} from "../../../servicios/api/api.service";
import {MedicoInterface} from "../../../modelos/medico.interface";

@Component({
  selector: 'app-nuevo-medico',
  templateUrl: './nuevo-medico.component.html',
  styleUrls: ['./nuevo-medico.component.css']
})
export class NuevoMedicoComponent implements  OnInit {


  constructor(private activeroute:ActivatedRoute, private router:Router, private api:ApiService) {

  }
  campos = true;
  nuevoForm = new FormGroup({
    usuario: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    nombre: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    apellidos: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    clave: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    numColegiado: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] })
  });

  ngOnInit(): void {
  }

  //comprobacion de los campos antes de hacer peticion
  lecturaCampos() {
    if (this.nuevoForm.controls.usuario.errors?.['required'] ||
      this.nuevoForm.controls.nombre.errors?.['required'] ||
      this.nuevoForm.controls.apellidos.errors?.['required'] ||
      this.nuevoForm.controls.clave.errors?.['required'] ||
      this.nuevoForm.controls.numColegiado.errors?.['required']

    ) {
      this.campos = false;
    }
    else {
      this.campos = true;
    }

  }

  postForm(form: MedicoInterface) {
    this.lecturaCampos()
    if (this.campos) {
      this.api.postMedico(form).subscribe(data =>{
        console.log(data);
        this.router.navigate(['medico']);
      })
    }
    
  }
  atras() {
    this.router.navigate(['medico']);
  }

}
