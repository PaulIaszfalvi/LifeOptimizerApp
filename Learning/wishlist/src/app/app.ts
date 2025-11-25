import { Component, signal } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { WishItem } from './shared/models/wishItem';

@Component({
  selector: 'app-root',
  imports: [RouterOutlet],
  templateUrl: './app.html',
  styleUrl: './app.css'
})
export class App {
  protected readonly title = signal('wishlist');
  items = [
    new WishItem('To Learn Angular'),
    new WishItem('To Stick with God'),
    new WishItem('To Learn from my mistakes'),
  ]
}
