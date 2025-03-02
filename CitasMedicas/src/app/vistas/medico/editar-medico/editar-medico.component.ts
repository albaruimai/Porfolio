import { Component , OnInit} from '@angular/core';
import {Router, ActivatedRoute} from "@angular/router";
import {ApiService} from "../../../servicios/api/api.service";
import {FormGroup, FormControl, Validators} from "@angular/forms";
import {MedicoInterface} from "../../../modelos/medico.interface";

@Component({
  selector: 'app-editar-medico',
  templateUrl: './editar-medico.component.html',
  styleUrls: ['./editar-medico.component.css']
})
export class EditarMedicoComponent implements OnInit{

  constructor(private activeroute:ActivatedRoute, private router:Router, private api:ApiService) {

  }

  campos = true;
  editarForm = new FormGroup({
    id: new FormControl<number>(0, { nonNullable: true}),
    usuario: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    nombre: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    apellidos: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    clave: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
    numColegiado: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] })
  });

  ngOnInit(): void {
    let medicoId = this.activeroute.snapshot.paramMap.get('id');
    if(medicoId!=null){
      this.api.getMedico(medicoId).subscribe(data=>{
        let datosMedico = data;
        this.editarForm.setValue({
          id: Number(medicoId)!,
          usuario: datosMedico.usuario!,
          nombre: datosMedico.nombre!,
          apellidos: datosMedico.apellidos!,
          clave: datosMedico.clave!,
          numColegiado: datosMedico.numColegiado!
        });
        console.log(this.editarForm.value);
      });

    }
  }


  //comprobacion de los campos antes de hacer peticion
  lecturaCampos() {
    if (this.editarForm.controls.usuario.errors?.['required'] ||
      this.editarForm.controls.nombre.errors?.['required'] ||
      this.editarForm.controls.apellidos.errors?.['required'] ||
      this.editarForm.controls.clave.errors?.['required'] ||
      this.editarForm.controls.numColegiado.errors?.['required']

    ) {
      this.campos = false;
    }
    else {
      this.campos = true;
    }

  }


  postForm(form: MedicoInterface) {
    this.lecturaCampos();
    if (this.campos) {
      this.api.putMedico(form).subscribe(data => {
        console.log(data);
        this.router.navigate(['medico']);
      })
    }
    

  }
  atras(){
    this.router.navigate(['verMedico', this.editarForm.value.id!]);
  }

}
