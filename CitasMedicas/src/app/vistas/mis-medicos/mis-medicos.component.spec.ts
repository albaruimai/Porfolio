import { ComponentFixture, TestBed } from '@angular/core/testing';

import { MisMedicosComponent } from './mis-medicos.component';

describe('MisMedicosComponent', () => {
  let component: MisMedicosComponent;
  let fixture: ComponentFixture<MisMedicosComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [MisMedicosComponent]
    });
    fixture = TestBed.createComponent(MisMedicosComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
